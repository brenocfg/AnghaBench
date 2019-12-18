#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  scalar_t__ uint32_t ;
typedef  void KHRN_POINTER_MAP_T ;
typedef  int /*<<< orphan*/  EGL_SYNC_T ;

/* Variables and functions */
 int /*<<< orphan*/  UNUSED (void*) ; 
 int /*<<< orphan*/  egl_sync_term (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  khrn_platform_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vcos_assert (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void egl_sync_destroy_iterator
   (KHRN_POINTER_MAP_T *sync_map, uint32_t sync, void *sync_handle, void *data)
{
   EGL_SYNC_T *sync_ptr = (EGL_SYNC_T *) sync;

   UNUSED(sync_map);
   UNUSED(sync_handle);
   UNUSED(data);

   vcos_assert(sync_ptr != NULL);

   egl_sync_term(sync_ptr);
   khrn_platform_free(sync_ptr);
}