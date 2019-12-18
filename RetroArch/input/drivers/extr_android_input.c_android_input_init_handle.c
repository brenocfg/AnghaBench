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
 int /*<<< orphan*/  RARCH_LOG (char*) ; 
 int /*<<< orphan*/  RTLD_DEFAULT ; 
 int RTLD_LAZY ; 
 int RTLD_LOCAL ; 
 int /*<<< orphan*/ * dlopen (char*,int) ; 
 void* dlsym (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  engine_handle_dpad ; 
 int /*<<< orphan*/  engine_handle_dpad_getaxisvalue ; 
 int /*<<< orphan*/ * libandroid_handle ; 
 void* p_AMotionEvent_getAxisValue ; 
 void* p_AMotionEvent_getButtonState ; 
 int pad_id1 ; 
 int pad_id2 ; 

__attribute__((used)) static bool android_input_init_handle(void)
{
#ifdef HAVE_DYNAMIC
   if (libandroid_handle != NULL) /* already initialized */
      return true;
#ifdef ANDROID_AARCH64
   if ((libandroid_handle = dlopen("/system/lib64/libandroid.so",
               RTLD_LOCAL | RTLD_LAZY)) == 0)
      return false;
#else
   if ((libandroid_handle = dlopen("/system/lib/libandroid.so",
               RTLD_LOCAL | RTLD_LAZY)) == 0)
      return false;
#endif

   if ((p_AMotionEvent_getAxisValue = dlsym(RTLD_DEFAULT,
               "AMotionEvent_getAxisValue")))
   {
      RARCH_LOG("Set engine_handle_dpad to 'Get Axis Value' (for reading extra analog sticks)");
      engine_handle_dpad = engine_handle_dpad_getaxisvalue;
   }

   p_AMotionEvent_getButtonState = dlsym(RTLD_DEFAULT,"AMotionEvent_getButtonState");
#endif

   pad_id1 = -1;
   pad_id2 = -1;

   return true;
}