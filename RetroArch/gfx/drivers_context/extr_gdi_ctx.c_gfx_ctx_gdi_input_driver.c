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
struct TYPE_10__ {int /*<<< orphan*/ * (* init ) (char const*) ;} ;
typedef  TYPE_3__ input_driver_t ;

/* Variables and functions */
 TYPE_2__* config_get_ptr () ; 
 int /*<<< orphan*/ * dinput_gdi ; 
 TYPE_3__ input_dinput ; 
 TYPE_3__ input_winraw ; 
 scalar_t__ string_is_equal (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/ * stub1 (char const*) ; 
 int /*<<< orphan*/ * stub2 (char const*) ; 

__attribute__((used)) static void gfx_ctx_gdi_input_driver(void *data,
      const char *joypad_name,
      input_driver_t **input, void **input_data)
{
#if _WIN32_WINNT >= 0x0501
   settings_t *settings = config_get_ptr();

   /* winraw only available since XP */
   if (string_is_equal(settings->arrays.input_driver, "raw"))
   {
      *input_data = input_winraw.init(joypad_name);
      if (*input_data)
      {
         *input     = &input_winraw;
         dinput_gdi = NULL;
         return;
      }
   }
#endif

#ifdef HAVE_DINPUT
   dinput_gdi  = input_dinput.init(joypad_name);
   *input      = dinput_gdi ? &input_dinput : NULL;
#else
   dinput_gdi  = NULL;
   *input      = NULL;
#endif
   *input_data = dinput_gdi;
}