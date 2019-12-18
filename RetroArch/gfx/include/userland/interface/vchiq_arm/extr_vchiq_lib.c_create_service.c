#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_5__ ;
typedef  struct TYPE_13__   TYPE_4__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ VCHI_CALLBACK_T ;
typedef  scalar_t__ VCHIQ_STATUS_T ;
struct TYPE_10__ {scalar_t__ callback; TYPE_2__* userdata; int /*<<< orphan*/  fourcc; } ;
struct TYPE_11__ {void* lib_handle; scalar_t__ vchi_callback; int peek_size; int is_client; void* handle; int /*<<< orphan*/ * peek_buf; int /*<<< orphan*/  fd; TYPE_1__ base; } ;
typedef  TYPE_2__ VCHIQ_SERVICE_T ;
struct TYPE_12__ {scalar_t__ callback; int /*<<< orphan*/  fourcc; TYPE_2__* userdata; } ;
typedef  TYPE_3__ VCHIQ_SERVICE_PARAMS_T ;
typedef  int VCHIQ_SERVICE_HANDLE_T ;
typedef  TYPE_4__* VCHIQ_INSTANCE_T ;
struct TYPE_14__ {int is_open; void* handle; int /*<<< orphan*/  is_vchi; TYPE_3__ params; } ;
typedef  TYPE_5__ VCHIQ_CREATE_SERVICE_T ;
struct TYPE_13__ {int used_services; int /*<<< orphan*/  mutex; int /*<<< orphan*/  fd; TYPE_2__* services; } ;

/* Variables and functions */
 int /*<<< orphan*/  RETRY (int,int /*<<< orphan*/ ) ; 
 scalar_t__ VCHIQ_ERROR ; 
 int /*<<< orphan*/  VCHIQ_IOC_CREATE_SERVICE ; 
 int VCHIQ_MAX_INSTANCE_SERVICES ; 
 void* VCHIQ_SERVICE_HANDLE_INVALID ; 
 scalar_t__ VCHIQ_SUCCESS ; 
 int handle_seq ; 
 int /*<<< orphan*/  ioctl (int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_5__*) ; 
 int /*<<< orphan*/  is_valid_instance (TYPE_4__*) ; 
 int /*<<< orphan*/  vcos_log_info (char*,void*,int,...) ; 
 int /*<<< orphan*/  vcos_mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vcos_mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static VCHIQ_STATUS_T
create_service(VCHIQ_INSTANCE_T instance,
   const VCHIQ_SERVICE_PARAMS_T *params,
   VCHI_CALLBACK_T vchi_callback,
   int is_open,
   VCHIQ_SERVICE_HANDLE_T *phandle)
{
   VCHIQ_SERVICE_T *service = NULL;
   VCHIQ_STATUS_T status = VCHIQ_SUCCESS;
   int i;

   if (!is_valid_instance(instance))
      return VCHIQ_ERROR;

   vcos_mutex_lock(&instance->mutex);

   /* Find a free service */
   if (is_open)
   {
      /* Find a free service */
      for (i = 0; i < instance->used_services; i++)
      {
         if (instance->services[i].lib_handle == VCHIQ_SERVICE_HANDLE_INVALID)
         {
            service = &instance->services[i];
            break;
         }
      }
   }
   else
   {
      for (i = (instance->used_services - 1); i >= 0; i--)
      {
         VCHIQ_SERVICE_T *srv = &instance->services[i];
         if (srv->lib_handle == VCHIQ_SERVICE_HANDLE_INVALID)
         {
            service = srv;
         }
         else if (
            (srv->base.fourcc == params->fourcc) &&
            ((srv->base.callback != params->callback) ||
            (srv->vchi_callback != vchi_callback)))
         {
            /* There is another server using this fourcc which doesn't match */
            vcos_log_info("service %x already using fourcc 0x%x",
               srv->lib_handle, params->fourcc);
            service = NULL;
            status = VCHIQ_ERROR;
            break;
         }
      }
   }

   if (!service && (status == VCHIQ_SUCCESS))
   {
      if (instance->used_services < VCHIQ_MAX_INSTANCE_SERVICES)
         service = &instance->services[instance->used_services++];
      else
         status = VCHIQ_ERROR;
   }

   if (service)
   {
      if (!handle_seq)
         handle_seq = VCHIQ_MAX_INSTANCE_SERVICES;
      service->lib_handle = handle_seq | (service - instance->services);
      handle_seq += VCHIQ_MAX_INSTANCE_SERVICES;
   }

   vcos_mutex_unlock(&instance->mutex);

   if (service)
   {
      VCHIQ_CREATE_SERVICE_T args;
      int ret;

      service->base.fourcc = params->fourcc;
      service->base.callback = params->callback;
      service->vchi_callback = vchi_callback;
      service->base.userdata = params->userdata;
      service->fd = instance->fd;
      service->peek_size = -1;
      service->peek_buf = NULL;
      service->is_client = is_open;

      args.params = *params;
      args.params.userdata = service;
      args.is_open = is_open;
      args.is_vchi = (params->callback == NULL);
      args.handle = VCHIQ_SERVICE_HANDLE_INVALID; /* OUT parameter */
      RETRY(ret, ioctl(instance->fd, VCHIQ_IOC_CREATE_SERVICE, &args));
      if (ret == 0)
         service->handle = args.handle;
      else
         status = VCHIQ_ERROR;
   }

   if (status == VCHIQ_SUCCESS)
   {
      *phandle = service->lib_handle;
      vcos_log_info("service handle %x lib_handle %x using fourcc 0x%x",
         service->handle, service->lib_handle, params->fourcc);
   }
   else
   {
      vcos_mutex_lock(&instance->mutex);

      if (service)
         service->lib_handle = VCHIQ_SERVICE_HANDLE_INVALID;

      vcos_mutex_unlock(&instance->mutex);

      *phandle = VCHIQ_SERVICE_HANDLE_INVALID;
   }

   return status;
}