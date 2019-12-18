#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int uint8_t ;
struct TYPE_5__ {int* input_joypad_map; } ;
struct TYPE_6__ {TYPE_1__ uints; } ;
typedef  TYPE_2__ settings_t ;
struct TYPE_7__ {int /*<<< orphan*/  ident; } ;

/* Variables and functions */
 int /*<<< orphan*/  WPAD_EXP_GAMECUBE ; 
 int /*<<< orphan*/  WPAD_EXP_NONE ; 
 TYPE_2__* config_get_ptr () ; 
 TYPE_3__ gx_joypad ; 
 int /*<<< orphan*/  gx_joypad_name (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  input_autoconfigure_connect (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  input_config_set_device_name (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * pad_type ; 

__attribute__((used)) static void check_port0_active(uint8_t pad_count)
{
   settings_t *settings = config_get_ptr();
   int idx = settings->uints.input_joypad_map[0];

   if(pad_count < 2 && idx != 0)
   {
#ifdef HW_RVL
      pad_type[0] = WPAD_EXP_NONE;
#else
      pad_type[0] = WPAD_EXP_GAMECUBE;
#endif
      settings->uints.input_joypad_map[0] = 0;
               
      input_autoconfigure_connect(
            gx_joypad_name(0),
            NULL,
            gx_joypad.ident,
            0, // port
            0,
            0
            );

      input_config_set_device_name(0, gx_joypad_name(0));
   }
}