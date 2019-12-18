#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
struct TYPE_11__ {TYPE_1__* priv; scalar_t__ alloc_size; int /*<<< orphan*/ * data; } ;
struct TYPE_10__ {int header_size; scalar_t__ payload_size; int /*<<< orphan*/  (* allocator_free ) (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ;int /*<<< orphan*/  allocator_context; scalar_t__ (* allocator_alloc ) (int /*<<< orphan*/ ,scalar_t__) ;} ;
struct TYPE_9__ {unsigned int headers_num; TYPE_4__** header; } ;
struct TYPE_8__ {int refcount; scalar_t__ payload_size; int /*<<< orphan*/  (* pf_payload_free ) (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ;int /*<<< orphan*/  payload_context; int /*<<< orphan*/ * payload; void* owner; int /*<<< orphan*/  pf_release; } ;
typedef  int /*<<< orphan*/  MMAL_STATUS_T ;
typedef  TYPE_2__ MMAL_POOL_T ;
typedef  TYPE_3__ MMAL_POOL_PRIVATE_T ;
typedef  TYPE_4__ MMAL_BUFFER_HEADER_T ;
typedef  scalar_t__ MMAL_BOOL_T ;

/* Variables and functions */
 int /*<<< orphan*/  ALIGN ; 
 int /*<<< orphan*/  LOG_ERROR (char*,unsigned int,unsigned int) ; 
 int /*<<< orphan*/  LOG_TRACE (char*,scalar_t__,unsigned int,unsigned int) ; 
 int /*<<< orphan*/  MMAL_ENOMEM ; 
 int /*<<< orphan*/  MMAL_SUCCESS ; 
 int ROUND_UP (int,int /*<<< orphan*/ ) ; 
 TYPE_4__* mmal_buffer_header_initialise (TYPE_4__*,int) ; 
 int /*<<< orphan*/  mmal_pool_buffer_header_release ; 
 scalar_t__ stub1 (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  stub2 (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static MMAL_STATUS_T mmal_pool_initialise_buffer_headers(MMAL_POOL_T *pool, unsigned int headers,
                                                         MMAL_BOOL_T reinitialise)
{
   MMAL_POOL_PRIVATE_T *private = (MMAL_POOL_PRIVATE_T *)pool;
   MMAL_BUFFER_HEADER_T *header;
   uint8_t *payload = NULL;
   unsigned int i;

   header = (MMAL_BUFFER_HEADER_T *)((uint8_t *)pool->header + ROUND_UP(sizeof(void *)*headers,ALIGN));

   for (i = 0; i < headers; i++)
   {
      if (reinitialise)
         header = mmal_buffer_header_initialise(header, private->header_size);

      if (private->payload_size && private->allocator_alloc)
      {
         LOG_TRACE("allocating %u bytes for payload %u/%u", private->payload_size, i, headers);
         payload = (uint8_t*)private->allocator_alloc(private->allocator_context, private->payload_size);
         if (! payload)
         {
            LOG_ERROR("failed to allocate payload %u/%u", i, headers);
            return MMAL_ENOMEM;
         }
      }
      else
      {
         if (header->priv->pf_payload_free && header->priv->payload && header->priv->payload_size)
         {
            LOG_TRACE("freeing %u bytes for payload %u/%u", header->priv->payload_size, i, headers);
            header->priv->pf_payload_free(header->priv->payload_context, header->priv->payload);
         }
      }
      header->data = payload;
      header->alloc_size = private->payload_size;
      header->priv->pf_release = mmal_pool_buffer_header_release;
      header->priv->owner = (void *)pool;
      header->priv->refcount = 1;
      header->priv->payload = payload;
      header->priv->payload_context = private->allocator_context;
      header->priv->pf_payload_free = private->allocator_free;
      header->priv->payload_size = private->payload_size;
      pool->header[i] = header;
      pool->headers_num = i+1;
      header = (MMAL_BUFFER_HEADER_T *)((uint8_t*)header + private->header_size);
   }

   return MMAL_SUCCESS;
}