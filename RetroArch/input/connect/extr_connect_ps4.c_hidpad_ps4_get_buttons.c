#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {scalar_t__ ps; scalar_t__ square; scalar_t__ cross; scalar_t__ circle; scalar_t__ triangle; scalar_t__ l1; scalar_t__ r1; scalar_t__ l2; scalar_t__ r2; scalar_t__ share; scalar_t__ options; scalar_t__ l3; scalar_t__ r3; } ;
struct ps4 {TYPE_1__ btn; } ;
struct hidpad_ps4_data {int /*<<< orphan*/  data; } ;
typedef  int /*<<< orphan*/  input_bits_t ;

/* Variables and functions */
 int /*<<< orphan*/  BIT256_CLEAR_ALL_PTR (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  BIT256_SET_PTR (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RARCH_MENU_TOGGLE ; 
 int /*<<< orphan*/  RETRO_DEVICE_ID_JOYPAD_A ; 
 int /*<<< orphan*/  RETRO_DEVICE_ID_JOYPAD_B ; 
 int /*<<< orphan*/  RETRO_DEVICE_ID_JOYPAD_DOWN ; 
 int /*<<< orphan*/  RETRO_DEVICE_ID_JOYPAD_L ; 
 int /*<<< orphan*/  RETRO_DEVICE_ID_JOYPAD_L2 ; 
 int /*<<< orphan*/  RETRO_DEVICE_ID_JOYPAD_L3 ; 
 int /*<<< orphan*/  RETRO_DEVICE_ID_JOYPAD_LEFT ; 
 int /*<<< orphan*/  RETRO_DEVICE_ID_JOYPAD_R ; 
 int /*<<< orphan*/  RETRO_DEVICE_ID_JOYPAD_R2 ; 
 int /*<<< orphan*/  RETRO_DEVICE_ID_JOYPAD_R3 ; 
 int /*<<< orphan*/  RETRO_DEVICE_ID_JOYPAD_RIGHT ; 
 int /*<<< orphan*/  RETRO_DEVICE_ID_JOYPAD_SELECT ; 
 int /*<<< orphan*/  RETRO_DEVICE_ID_JOYPAD_START ; 
 int /*<<< orphan*/  RETRO_DEVICE_ID_JOYPAD_UP ; 
 int /*<<< orphan*/  RETRO_DEVICE_ID_JOYPAD_X ; 
 int /*<<< orphan*/  RETRO_DEVICE_ID_JOYPAD_Y ; 
 scalar_t__ hidpad_ps4_check_dpad (struct ps4*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void hidpad_ps4_get_buttons(void *data, input_bits_t* state)
{
   struct hidpad_ps4_data *device = (struct hidpad_ps4_data*)data;
   struct ps4                *rpt = device ?
      (struct ps4*)&device->data : NULL;

   if (!device || !rpt)
      return;

   BIT256_CLEAR_ALL_PTR( state );

   if (rpt->btn.r3)
      BIT256_SET_PTR( state, RETRO_DEVICE_ID_JOYPAD_R3 );
   if (rpt->btn.l3)
      BIT256_SET_PTR( state, RETRO_DEVICE_ID_JOYPAD_L3 );
   if (rpt->btn.options)
      BIT256_SET_PTR( state, RETRO_DEVICE_ID_JOYPAD_START );
   if ( rpt->btn.share)
      BIT256_SET_PTR( state, RETRO_DEVICE_ID_JOYPAD_SELECT );
   if ( rpt->btn.r2)
      BIT256_SET_PTR( state, RETRO_DEVICE_ID_JOYPAD_R2 );
   if (rpt->btn.l2)
      BIT256_SET_PTR( state, RETRO_DEVICE_ID_JOYPAD_L2 );
   if (rpt->btn.r1)
      BIT256_SET_PTR( state, RETRO_DEVICE_ID_JOYPAD_R );
   if (rpt->btn.l1)
      BIT256_SET_PTR( state, RETRO_DEVICE_ID_JOYPAD_L );
   if (rpt->btn.triangle)
      BIT256_SET_PTR( state, RETRO_DEVICE_ID_JOYPAD_X );
   if (rpt->btn.circle)
      BIT256_SET_PTR( state, RETRO_DEVICE_ID_JOYPAD_A );
   if (rpt->btn.cross)
      BIT256_SET_PTR( state, RETRO_DEVICE_ID_JOYPAD_B );
   if (rpt->btn.square)
      BIT256_SET_PTR( state, RETRO_DEVICE_ID_JOYPAD_Y );
   if ((hidpad_ps4_check_dpad(rpt, RETRO_DEVICE_ID_JOYPAD_LEFT)))
      BIT256_SET_PTR( state, RETRO_DEVICE_ID_JOYPAD_LEFT );
   if ((hidpad_ps4_check_dpad(rpt, RETRO_DEVICE_ID_JOYPAD_DOWN)))
      BIT256_SET_PTR( state, RETRO_DEVICE_ID_JOYPAD_DOWN );
   if ((hidpad_ps4_check_dpad(rpt, RETRO_DEVICE_ID_JOYPAD_RIGHT)))
      BIT256_SET_PTR( state, RETRO_DEVICE_ID_JOYPAD_RIGHT );
   if ((hidpad_ps4_check_dpad(rpt, RETRO_DEVICE_ID_JOYPAD_UP)))
      BIT256_SET_PTR( state, RETRO_DEVICE_ID_JOYPAD_UP );
   if (rpt->btn.ps)
      BIT256_SET_PTR( state, RARCH_MENU_TOGGLE );
}