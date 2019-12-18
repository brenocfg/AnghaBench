#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int /*<<< orphan*/  uint32_t ;
struct TYPE_3__ {scalar_t__ handle; int /*<<< orphan*/ * mem; } ;
typedef  TYPE_1__ MMAL_VC_PAYLOAD_ELEM_T ;

/* Variables and functions */
 int /*<<< orphan*/  MMAL_PARAM_UNUSED (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 TYPE_1__* mmal_vc_payload_list_find_handle (int /*<<< orphan*/ *) ; 
 void* vcsm_lock (unsigned int) ; 

uint8_t *mmal_vc_shm_lock(uint8_t *mem, uint32_t workaround)
{
   /* Zero copy stuff */
   MMAL_VC_PAYLOAD_ELEM_T *elem = mmal_vc_payload_list_find_handle(mem);
   MMAL_PARAM_UNUSED(workaround);

   if (elem) {
      mem = elem->mem;
#ifdef ENABLE_MMAL_VCSM
      void *p = vcsm_lock((unsigned int)elem->handle);
      if (!p)
         assert(0);
#endif /* ENABLE_MMAL_VCSM */
   }

   return mem;
}