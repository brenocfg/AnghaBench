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
struct TYPE_2__ {scalar_t__ home; scalar_t__ up; scalar_t__ right; scalar_t__ down; scalar_t__ left; scalar_t__ y; scalar_t__ b; scalar_t__ a; scalar_t__ x; scalar_t__ l; scalar_t__ r; scalar_t__ zl; scalar_t__ zr; scalar_t__ minus; scalar_t__ plus; scalar_t__ l3; scalar_t__ r3; } ;
struct wiiupro {TYPE_1__ btn; } ;
struct hidpad_wiiupro_data {int /*<<< orphan*/  data; } ;
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

__attribute__((used)) static void hidpad_wiiupro_get_buttons(void *data, input_bits_t *state)
{
   struct hidpad_wiiupro_data *device = (struct hidpad_wiiupro_data*)data;
   struct wiiupro                *rpt = device ?
      (struct wiiupro*)&device->data : NULL;

   if (!device || !rpt)
      return;

   BIT256_CLEAR_ALL_PTR(state);

   if (rpt->btn.r3)
      BIT256_SET_PTR(state, RETRO_DEVICE_ID_JOYPAD_R3);
   if (rpt->btn.l3)
      BIT256_SET_PTR(state, RETRO_DEVICE_ID_JOYPAD_L3);
   if (rpt->btn.plus)
      BIT256_SET_PTR(state, RETRO_DEVICE_ID_JOYPAD_START);
   if ( rpt->btn.minus)
      BIT256_SET_PTR(state, RETRO_DEVICE_ID_JOYPAD_SELECT);
   if ( rpt->btn.zr)
      BIT256_SET_PTR(state, RETRO_DEVICE_ID_JOYPAD_R2);
   if ( rpt->btn.zl)
      BIT256_SET_PTR(state, RETRO_DEVICE_ID_JOYPAD_L2);
   if ( rpt->btn.r)
      BIT256_SET_PTR(state, RETRO_DEVICE_ID_JOYPAD_R);
   if ( rpt->btn.l)
      BIT256_SET_PTR(state, RETRO_DEVICE_ID_JOYPAD_L);
   if ( rpt->btn.x)
      BIT256_SET_PTR(state, RETRO_DEVICE_ID_JOYPAD_X);
   if ( rpt->btn.a)
      BIT256_SET_PTR(state, RETRO_DEVICE_ID_JOYPAD_A);
   if ( rpt->btn.b)
      BIT256_SET_PTR(state, RETRO_DEVICE_ID_JOYPAD_B);
   if ( rpt->btn.y)
      BIT256_SET_PTR(state, RETRO_DEVICE_ID_JOYPAD_Y);
   if ( rpt->btn.left)
      BIT256_SET_PTR(state, RETRO_DEVICE_ID_JOYPAD_LEFT);
   if ( rpt->btn.down)
      BIT256_SET_PTR(state, RETRO_DEVICE_ID_JOYPAD_DOWN);
   if ( rpt->btn.right)
      BIT256_SET_PTR(state, RETRO_DEVICE_ID_JOYPAD_RIGHT);
   if ( rpt->btn.up)
      BIT256_SET_PTR(state, RETRO_DEVICE_ID_JOYPAD_UP);
   if ( rpt->btn.home)
      BIT256_SET_PTR(state, RARCH_MENU_TOGGLE);
}