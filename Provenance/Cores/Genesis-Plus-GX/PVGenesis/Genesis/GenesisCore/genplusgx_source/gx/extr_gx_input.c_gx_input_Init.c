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
 int /*<<< orphan*/  PAD_Init () ; 
 int /*<<< orphan*/  WPAD_CHAN_ALL ; 
 int /*<<< orphan*/  WPAD_FMT_BTNS_ACC_IR ; 
 int /*<<< orphan*/  WPAD_Init () ; 
 int /*<<< orphan*/  WPAD_SetDataFormat (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WPAD_SetIdleTimeout (int) ; 
 int /*<<< orphan*/  WPAD_SetVRes (int /*<<< orphan*/ ,int,int) ; 

void gx_input_Init(void)
{
  PAD_Init();
#ifdef HW_RVL
  WPAD_Init();
  WPAD_SetIdleTimeout(60);
  WPAD_SetDataFormat(WPAD_CHAN_ALL,WPAD_FMT_BTNS_ACC_IR);
  WPAD_SetVRes(WPAD_CHAN_ALL,640,480);
#endif
}