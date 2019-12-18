#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_11__ {int /*<<< orphan*/  (* set_axis_value ) (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;} ;
struct TYPE_10__ {int button_state; int /*<<< orphan*/  analog_state; } ;
struct TYPE_8__ {int /*<<< orphan*/  stick_y; int /*<<< orphan*/  stick_x; } ;
struct TYPE_7__ {int btns_h; int /*<<< orphan*/  rstick_y; int /*<<< orphan*/  rstick_x; int /*<<< orphan*/  lstick_y; int /*<<< orphan*/  lstick_x; } ;
struct TYPE_9__ {int device_type; int btns_h; TYPE_2__ nunchuck; TYPE_1__ classic; } ;
typedef  TYPE_3__ KPADData ;

/* Variables and functions */
 int CLASSIC_BUTTON_MASK ; 
#define  WIIMOTE_TYPE_CLASSIC 131 
#define  WIIMOTE_TYPE_NUNCHUK 130 
#define  WIIMOTE_TYPE_PRO 129 
#define  WIIMOTE_TYPE_WIIPLUS 128 
 int WIIU_PRO_BUTTON_MASK ; 
 int /*<<< orphan*/  WIIU_READ_STICK (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kpad_register (unsigned int,int) ; 
 TYPE_5__ pad_functions ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub2 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub3 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub4 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_4__* wiimotes ; 

__attribute__((used)) static void kpad_poll_one_channel(unsigned channel, KPADData *kpad)
{
   kpad_register(channel, kpad->device_type);
   switch(kpad->device_type)
   {
      case WIIMOTE_TYPE_PRO:
         wiimotes[channel].button_state = kpad->classic.btns_h
            & ~WIIU_PRO_BUTTON_MASK;
         pad_functions.set_axis_value(wiimotes[channel].analog_state,
               WIIU_READ_STICK(kpad->classic.lstick_x),
               WIIU_READ_STICK(kpad->classic.lstick_y),
               WIIU_READ_STICK(kpad->classic.rstick_x),
               WIIU_READ_STICK(kpad->classic.rstick_y), 0, 0);
         break;
      case WIIMOTE_TYPE_CLASSIC:
         wiimotes[channel].button_state = kpad->classic.btns_h
            & ~CLASSIC_BUTTON_MASK;
         pad_functions.set_axis_value(wiimotes[channel].analog_state,
               WIIU_READ_STICK(kpad->classic.lstick_x),
               WIIU_READ_STICK(kpad->classic.lstick_y),
               WIIU_READ_STICK(kpad->classic.rstick_x),
               WIIU_READ_STICK(kpad->classic.rstick_y), 0, 0);
         break;
      case WIIMOTE_TYPE_NUNCHUK:
         wiimotes[channel].button_state = kpad->btns_h;
         pad_functions.set_axis_value(wiimotes[channel].analog_state,
               WIIU_READ_STICK(kpad->nunchuck.stick_x),
               WIIU_READ_STICK(kpad->nunchuck.stick_y), 0, 0, 0, 0);
         break;
      case WIIMOTE_TYPE_WIIPLUS:
         wiimotes[channel].button_state = kpad->btns_h;
         pad_functions.set_axis_value(wiimotes[channel].analog_state,
               0, 0, 0, 0, 0, 0);
         break;
   }
}