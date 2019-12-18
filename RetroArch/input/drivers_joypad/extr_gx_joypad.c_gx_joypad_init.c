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
 int DEFAULT_MAX_PADS ; 
 int /*<<< orphan*/  PAD_Init () ; 
 int /*<<< orphan*/  SYS_SetPowerCallback (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SYS_SetResetCallback (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WPADInit () ; 
 int /*<<< orphan*/  WPAD_CHAN_ALL ; 
 int /*<<< orphan*/  WPAD_EXP_NOCONTROLLER ; 
 int /*<<< orphan*/  WPAD_FMT_BTNS_ACC_IR ; 
 int /*<<< orphan*/  WPAD_SetDataFormat (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WPAD_SetVRes (int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  gx_joypad_poll () ; 
 int /*<<< orphan*/ * pad_type ; 
 int /*<<< orphan*/  power_callback ; 
 int /*<<< orphan*/  reset_cb ; 

__attribute__((used)) static bool gx_joypad_init(void *data)
{
   int i;
   SYS_SetResetCallback(reset_cb);
#ifdef HW_RVL
   SYS_SetPowerCallback(power_callback);
#endif

   (void)data;

   for (i = 0; i < DEFAULT_MAX_PADS; i++)
      pad_type[i] = WPAD_EXP_NOCONTROLLER;

   PAD_Init();
#ifdef HW_RVL
   WPADInit();
   /* Set IR for all wiimotes */
   WPAD_SetVRes(WPAD_CHAN_ALL,640,480);
   WPAD_SetDataFormat(WPAD_CHAN_ALL,WPAD_FMT_BTNS_ACC_IR);
#endif

   gx_joypad_poll();

   return true;
}