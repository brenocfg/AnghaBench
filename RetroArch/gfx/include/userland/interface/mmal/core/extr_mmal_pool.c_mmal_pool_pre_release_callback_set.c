#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
struct TYPE_5__ {int header_size; } ;
struct TYPE_4__ {int headers_num; scalar_t__ header; } ;
typedef  TYPE_1__ MMAL_POOL_T ;
typedef  TYPE_2__ MMAL_POOL_PRIVATE_T ;
typedef  int /*<<< orphan*/  MMAL_BUFFER_HEADER_T ;
typedef  int /*<<< orphan*/  MMAL_BH_PRE_RELEASE_CB_T ;

/* Variables and functions */
 int /*<<< orphan*/  ALIGN ; 
 int ROUND_UP (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mmal_buffer_header_pre_release_cb_set (int /*<<< orphan*/ *,int /*<<< orphan*/ ,void*) ; 

void mmal_pool_pre_release_callback_set(MMAL_POOL_T *pool, MMAL_BH_PRE_RELEASE_CB_T cb, void *userdata)
{
   unsigned int i;
   MMAL_POOL_PRIVATE_T *private = (MMAL_POOL_PRIVATE_T *)pool;
   MMAL_BUFFER_HEADER_T *header =
         (MMAL_BUFFER_HEADER_T*)((uint8_t*)pool->header + ROUND_UP(sizeof(void*)*pool->headers_num,ALIGN));

   for (i = 0; i < pool->headers_num; ++i)
   {
      mmal_buffer_header_pre_release_cb_set(header, cb, userdata);
      header = (MMAL_BUFFER_HEADER_T *)((uint8_t*)header + private->header_size);
   }
}