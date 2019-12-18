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
struct TYPE_8__ {int /*<<< orphan*/  input_driver; } ;
struct TYPE_9__ {TYPE_1__ arrays; } ;
typedef  TYPE_2__ settings_t ;
struct TYPE_10__ {void* (* init ) (char const*) ;} ;
typedef  TYPE_3__ input_driver_t ;

/* Variables and functions */
 TYPE_2__* config_get_ptr () ; 
 TYPE_3__ input_linuxraw ; 
 TYPE_3__ input_udev ; 
 scalar_t__ string_is_equal (int /*<<< orphan*/ ,char*) ; 
 void* stub1 (char const*) ; 
 void* stub2 (char const*) ; 

__attribute__((used)) static void gfx_ctx_khr_display_input_driver(void *data,
      const char *joypad_name,
      input_driver_t **input, void **input_data)
{
#ifdef HAVE_X11
   settings_t *settings = config_get_ptr();

   /* We cannot use the X11 input driver for DRM/KMS */
   if (string_is_equal(settings->arrays.input_driver, "x"))
   {
#ifdef HAVE_UDEV
      {
         /* Try to set it to udev instead */
         void *udev = input_udev.init(joypad_name);
         if (udev)
         {
            *input       = &input_udev;
            *input_data  = udev;
            return;
         }
      }
#endif
#if defined(__linux__) && !defined(ANDROID)
      {
         /* Try to set it to linuxraw instead */
         void *linuxraw = input_linuxraw.init(joypad_name);
         if (linuxraw)
         {
            *input       = &input_linuxraw;
            *input_data  = linuxraw;
            return;
         }
      }
#endif
   }
#endif

   *input      = NULL;
   *input_data = NULL;
}