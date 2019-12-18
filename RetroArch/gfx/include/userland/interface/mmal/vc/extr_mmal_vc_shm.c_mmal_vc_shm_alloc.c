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
typedef  scalar_t__ uint32_t ;
struct TYPE_4__ {void* vc_handle; void* handle; int /*<<< orphan*/ * mem; } ;
typedef  TYPE_1__ MMAL_VC_PAYLOAD_ELEM_T ;

/* Variables and functions */
 int /*<<< orphan*/  LOG_ERROR (char*,...) ; 
 int /*<<< orphan*/  MMAL_PARAM_UNUSED (scalar_t__) ; 
 int /*<<< orphan*/  VCSM_CACHE_TYPE_HOST ; 
 TYPE_1__* mmal_vc_payload_list_get () ; 
 int /*<<< orphan*/  mmal_vc_payload_list_release (TYPE_1__*) ; 
 int /*<<< orphan*/  vcsm_free (unsigned int) ; 
 scalar_t__ vcsm_lock (unsigned int) ; 
 unsigned int vcsm_malloc_cache (scalar_t__,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  vcsm_unlock_hdl (unsigned int) ; 
 unsigned int vcsm_vc_hdl_from_hdl (unsigned int) ; 

uint8_t *mmal_vc_shm_alloc(uint32_t size)
{
   uint8_t *mem = NULL;

   MMAL_VC_PAYLOAD_ELEM_T *payload_elem = mmal_vc_payload_list_get();
   if (!payload_elem)
   {
      LOG_ERROR("could not get a free slot in the payload list");
      return NULL;
   }

#ifdef ENABLE_MMAL_VCSM
   unsigned int vcsm_handle = vcsm_malloc_cache(size, VCSM_CACHE_TYPE_HOST, "mmal_vc_port buffer");
   unsigned int vc_handle = vcsm_vc_hdl_from_hdl(vcsm_handle);
   mem = (uint8_t *)vcsm_lock( vcsm_handle );
   if (!mem || !vc_handle)
   {
      LOG_ERROR("could not allocate %i bytes of shared memory (handle %x)",
                (int)size, vcsm_handle);
      if (mem)
         vcsm_unlock_hdl(vcsm_handle);
      if (vcsm_handle)
         vcsm_free(vcsm_handle);
      mmal_vc_payload_list_release(payload_elem);
      return NULL;
   }

   /* The memory area is automatically mem-locked by vcsm's fault
    * handler when it is next used. So leave it unlocked until it
    * is needed.
    */
   vcsm_unlock_hdl(vcsm_handle);

   payload_elem->mem = mem;
   payload_elem->handle = (void *)vcsm_handle;
   payload_elem->vc_handle = (void *)vc_handle;
#else /* ENABLE_MMAL_VCSM */
   MMAL_PARAM_UNUSED(size);
   mmal_vc_payload_list_release(payload_elem);
#endif /* ENABLE_MMAL_VCSM */

   return mem;
}