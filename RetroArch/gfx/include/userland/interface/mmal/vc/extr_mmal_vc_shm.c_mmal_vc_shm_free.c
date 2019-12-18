#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
struct TYPE_4__ {scalar_t__ handle; } ;
typedef  TYPE_1__ MMAL_VC_PAYLOAD_ELEM_T ;
typedef  int /*<<< orphan*/  MMAL_STATUS_T ;

/* Variables and functions */
 int /*<<< orphan*/  MMAL_EINVAL ; 
 int /*<<< orphan*/  MMAL_SUCCESS ; 
 TYPE_1__* mmal_vc_payload_list_find_mem (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mmal_vc_payload_list_release (TYPE_1__*) ; 
 int /*<<< orphan*/  vcsm_free (unsigned int) ; 

MMAL_STATUS_T mmal_vc_shm_free(uint8_t *mem)
{
   MMAL_VC_PAYLOAD_ELEM_T *payload_elem = mmal_vc_payload_list_find_mem(mem);
   if (payload_elem)
   {
#ifdef ENABLE_MMAL_VCSM
      vcsm_free((unsigned int)payload_elem->handle);
#endif /* ENABLE_MMAL_VCSM */
      mmal_vc_payload_list_release(payload_elem);
      return MMAL_SUCCESS;
   }

   return MMAL_EINVAL;
}