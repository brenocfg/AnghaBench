#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int /*<<< orphan*/  uint32_t ;
struct TYPE_8__ {int /*<<< orphan*/  magic; int /*<<< orphan*/  msgid; } ;
typedef  TYPE_1__ mmal_worker_msg_header ;
typedef  scalar_t__ VCHIQ_STATUS_T ;
struct TYPE_9__ {size_t member_1; TYPE_1__* member_0; } ;
typedef  TYPE_2__ VCHIQ_ELEMENT_T ;
struct TYPE_10__ {int /*<<< orphan*/  bulk_lock; int /*<<< orphan*/  service; int /*<<< orphan*/  inited; } ;
typedef  int /*<<< orphan*/  MMAL_STATUS_T ;
typedef  TYPE_3__ MMAL_CLIENT_T ;
typedef  int MMAL_BOOL_T ;

/* Variables and functions */
 int /*<<< orphan*/  LOG_ERROR (char*) ; 
 int /*<<< orphan*/  LOG_TRACE (char*,size_t,...) ; 
 int /*<<< orphan*/  MMAL_EINVAL ; 
 int /*<<< orphan*/  MMAL_EIO ; 
 int /*<<< orphan*/  MMAL_MAGIC ; 
 int /*<<< orphan*/  MMAL_SUCCESS ; 
 scalar_t__ VCHIQ_SUCCESS ; 
 scalar_t__ vchiq_queue_bulk_transmit (int /*<<< orphan*/ ,int /*<<< orphan*/ *,size_t,TYPE_1__*) ; 
 scalar_t__ vchiq_queue_message (int /*<<< orphan*/ ,TYPE_2__*,int) ; 
 int /*<<< orphan*/  vcos_assert (int) ; 
 int /*<<< orphan*/  vcos_mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vcos_mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vcos_verify (int) ; 

MMAL_STATUS_T mmal_vc_send_message(MMAL_CLIENT_T *client,
                                   mmal_worker_msg_header *msg_header, size_t size,
                                   uint8_t *data, size_t data_size,
                                   uint32_t msgid)
{
   VCHIQ_STATUS_T vst;
   VCHIQ_ELEMENT_T elems[] = {{msg_header, size}};
   MMAL_BOOL_T using_bulk_transfer = (data_size != 0);

   LOG_TRACE("len %d", data_size);
   vcos_assert(size >= sizeof(mmal_worker_msg_header));

   if (!client->inited)
   {
      vcos_assert(0);
      return MMAL_EINVAL;
   }

   if (using_bulk_transfer)
      vcos_mutex_lock(&client->bulk_lock);

   msg_header->msgid  = msgid;
   msg_header->magic  = MMAL_MAGIC;

   vst = vchiq_queue_message(client->service, elems, 1);

   if (vst != VCHIQ_SUCCESS)
   {
      if (using_bulk_transfer)
         vcos_mutex_unlock(&client->bulk_lock);

      LOG_ERROR("failed");
      goto error;
   }

   if (using_bulk_transfer)
   {
      LOG_TRACE("bulk transmit: %p, %i", data, data_size);

      data_size = (data_size + 3) & ~3;
      vst = vchiq_queue_bulk_transmit(client->service, data, data_size, msg_header);

      vcos_mutex_unlock(&client->bulk_lock);

      if (!vcos_verify(vst == VCHIQ_SUCCESS))
      {
         LOG_ERROR("failed bulk transmit");
         /* This really should not happen and if it does, things will go wrong as
          * we've already queued the vchiq message above. */
         vcos_assert(0);
         goto error;
      }
   }

   return MMAL_SUCCESS;

 error:
   return MMAL_EIO;
}