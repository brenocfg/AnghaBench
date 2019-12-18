#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_3__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
struct TYPE_5__ {int /*<<< orphan*/  lock; TYPE_1__* list; } ;
struct TYPE_4__ {int /*<<< orphan*/ * mem; int /*<<< orphan*/  in_use; } ;
typedef  TYPE_1__ MMAL_VC_PAYLOAD_ELEM_T ;

/* Variables and functions */
 unsigned int MMAL_VC_PAYLOAD_ELEM_MAX ; 
 TYPE_3__ mmal_vc_payload_list ; 
 int /*<<< orphan*/  vcos_mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vcos_mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static MMAL_VC_PAYLOAD_ELEM_T *mmal_vc_payload_list_find_mem(uint8_t *mem)
{
   MMAL_VC_PAYLOAD_ELEM_T *elem = 0;
   unsigned int i;

   vcos_mutex_lock(&mmal_vc_payload_list.lock);
   for (i = 0; i < MMAL_VC_PAYLOAD_ELEM_MAX; i++)
   {
      if (!mmal_vc_payload_list.list[i].in_use)
         continue;
      if (mmal_vc_payload_list.list[i].mem != mem)
         continue;
      elem = &mmal_vc_payload_list.list[i];
      break;
   }
   vcos_mutex_unlock(&mmal_vc_payload_list.lock);

   return elem;
}