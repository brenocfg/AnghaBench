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

/* Variables and functions */
 int VCOS_DL_GLOBAL ; 
 int VCOS_DL_LAZY ; 
 int VCOS_DL_LOCAL ; 
 int /*<<< orphan*/ * local_eglIntOpenMAXILDoneMarker ; 
 int /*<<< orphan*/  vc_assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vcos_dlclose (void*) ; 
 void* vcos_dlopen (char*,int) ; 
 scalar_t__ vcos_dlsym (void*,char*) ; 

__attribute__((used)) static void load_eglIntOpenMAXILDoneMarker(void)
{
   void *handle;

   /* First try to load from the current process, this will succeed
    * if something that is linked to libEGL is already loaded or
    * something explicitly loaded libEGL with RTLD_GLOBAL
    */
   handle = vcos_dlopen(NULL, VCOS_DL_GLOBAL);
   local_eglIntOpenMAXILDoneMarker = (void * )vcos_dlsym(handle, "eglIntOpenMAXILDoneMarker");
   if (local_eglIntOpenMAXILDoneMarker == NULL)
   {
      vcos_dlclose(handle);
      /* If that failed try to load libEGL.so explicitely */
      handle = vcos_dlopen("libEGL.so", VCOS_DL_LAZY | VCOS_DL_LOCAL);
      vc_assert(handle != NULL);
      local_eglIntOpenMAXILDoneMarker = (void * )vcos_dlsym(handle, "eglIntOpenMAXILDoneMarker");
      vc_assert(local_eglIntOpenMAXILDoneMarker != NULL);
   }
}