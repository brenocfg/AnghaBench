#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_4__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  vchiq_params ;
typedef  scalar_t__ VCHIQ_STATUS_T ;
struct TYPE_5__ {int /*<<< orphan*/  version_min; int /*<<< orphan*/  version; TYPE_4__* userdata; int /*<<< orphan*/  callback; int /*<<< orphan*/  fourcc; } ;
typedef  TYPE_1__ VCHIQ_SERVICE_PARAMS_T ;
struct TYPE_6__ {int usecount; int inited; int /*<<< orphan*/  lock; int /*<<< orphan*/  refcount; int /*<<< orphan*/  service; int /*<<< orphan*/  waitpool; int /*<<< orphan*/  bulk_lock; } ;
typedef  scalar_t__ MMAL_STATUS_T ;
typedef  int MMAL_BOOL_T ;

/* Variables and functions */
 int /*<<< orphan*/  LOG_ERROR (char*) ; 
 int /*<<< orphan*/  MMAL_CONTROL_FOURCC () ; 
 scalar_t__ MMAL_EIO ; 
 scalar_t__ MMAL_ENOSPC ; 
 scalar_t__ MMAL_SUCCESS ; 
 scalar_t__ VCHIQ_SUCCESS ; 
 int /*<<< orphan*/  VCOS_LOG_CATEGORY ; 
 scalar_t__ VCOS_SUCCESS ; 
 int /*<<< orphan*/  WORKER_VER_MAJOR ; 
 int /*<<< orphan*/  WORKER_VER_MINIMUM ; 
 TYPE_4__ client ; 
 scalar_t__ create_waitpool (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  destroy_waitpool (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  init_once ; 
 int /*<<< orphan*/  memset (TYPE_1__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mmal_vc_release () ; 
 int /*<<< orphan*/  mmal_vc_vchiq_callback ; 
 int /*<<< orphan*/  mmal_vchiq_instance ; 
 int /*<<< orphan*/  once ; 
 int /*<<< orphan*/  vchiq_close_service (int /*<<< orphan*/ ) ; 
 scalar_t__ vchiq_connect (int /*<<< orphan*/ ) ; 
 scalar_t__ vchiq_initialise_fd (int /*<<< orphan*/ *,int) ; 
 scalar_t__ vchiq_open_service (int /*<<< orphan*/ ,TYPE_1__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vchiq_shutdown (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vcos_log_register (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vcos_log_unregister (int /*<<< orphan*/ ) ; 
 scalar_t__ vcos_mutex_create (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  vcos_mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vcos_mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vcos_once (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

MMAL_STATUS_T mmal_vc_init_fd(int dev_vchiq_fd)
{
   VCHIQ_SERVICE_PARAMS_T vchiq_params;
   MMAL_BOOL_T vchiq_initialised = 0, waitpool_initialised = 0;
   MMAL_BOOL_T service_initialised = 0;
   MMAL_STATUS_T status = MMAL_EIO;
   VCHIQ_STATUS_T vchiq_status;
   int count;

   vcos_once(&once, init_once);

   vcos_mutex_lock(&client.lock);

   count = client.refcount++;
   if (count > 0)
   {
      /* Already initialised so nothing to do */
      vcos_mutex_unlock(&client.lock);
      return MMAL_SUCCESS;
   }

   vcos_log_register("mmalipc", VCOS_LOG_CATEGORY);

   /* Initialise a VCHIQ instance */
   vchiq_status = vchiq_initialise_fd(&mmal_vchiq_instance, dev_vchiq_fd);
   if (vchiq_status != VCHIQ_SUCCESS)
   {
      LOG_ERROR("failed to initialise vchiq");
      status = MMAL_EIO;
      goto error;
   }
   vchiq_initialised = 1;

   vchiq_status = vchiq_connect(mmal_vchiq_instance);
   if (vchiq_status != VCHIQ_SUCCESS)
   {
      LOG_ERROR("failed to connect to vchiq");
      status = MMAL_EIO;
      goto error;
   }

   memset(&vchiq_params,0,sizeof(vchiq_params));
   vchiq_params.fourcc = MMAL_CONTROL_FOURCC();
   vchiq_params.callback = mmal_vc_vchiq_callback;
   vchiq_params.userdata = &client;
   vchiq_params.version = WORKER_VER_MAJOR;
   vchiq_params.version_min = WORKER_VER_MINIMUM;

   vchiq_status = vchiq_open_service(mmal_vchiq_instance, &vchiq_params, &client.service);
   if (vchiq_status != VCHIQ_SUCCESS)
   {
      LOG_ERROR("could not open vchiq service");
      status = MMAL_EIO;
      goto error;
   }
   client.usecount = 1; /* usecount set to 1 by the open call. */
   service_initialised = 1;

   status = create_waitpool(&client.waitpool);
   if (status != MMAL_SUCCESS)
   {
      LOG_ERROR("could not create wait pool");
      goto error;
   }
   waitpool_initialised = 1;

   if (vcos_mutex_create(&client.bulk_lock, "mmal client bulk lock") != VCOS_SUCCESS)
   {
      LOG_ERROR("could not create bulk lock");
      status = MMAL_ENOSPC;
      goto error;
   }

   client.inited = 1;

   vcos_mutex_unlock(&client.lock);
   /* assume we're not using VC immediately.  Do this outside the lock */
   mmal_vc_release();

   return MMAL_SUCCESS;

 error:
   if (waitpool_initialised)
      destroy_waitpool(&client.waitpool);
   if (service_initialised)
   {
      client.usecount = 0;
      vchiq_close_service(client.service);
   }
   if (vchiq_initialised)
      vchiq_shutdown(mmal_vchiq_instance);
   vcos_log_unregister(VCOS_LOG_CATEGORY);
   client.refcount--;

   vcos_mutex_unlock(&client.lock);
   return status;
}