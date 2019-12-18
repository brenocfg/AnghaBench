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
 TYPE_3__ input_udev ; 
 TYPE_3__ input_x ; 
 scalar_t__ string_is_equal (int /*<<< orphan*/ ,char*) ; 
 void* stub1 (char const*) ; 
 void* stub2 (char const*) ; 

__attribute__((used)) static void gfx_ctx_x_input_driver(void *data,
      const char *joypad_name,
      input_driver_t **input, void **input_data)
{
   void *x_input         = NULL;
#ifdef HAVE_UDEV
   settings_t *settings = config_get_ptr();

   if (string_is_equal(settings->arrays.input_driver, "udev"))
   {
      *input_data = input_udev.init(joypad_name);
      if (*input_data)
      {
         *input = &input_udev;
         return;
      }
   }
#endif

   x_input      = input_x.init(joypad_name);
   *input       = x_input ? &input_x : NULL;
   *input_data  = x_input;
}