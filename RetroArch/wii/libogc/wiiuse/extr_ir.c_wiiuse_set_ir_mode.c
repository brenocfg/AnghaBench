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
typedef  int ubyte ;
struct wiimote_t {int dummy; } ;

/* Variables and functions */
 scalar_t__ WIIMOTE_IS_SET (struct wiimote_t*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WIIMOTE_STATE_EXP ; 
 int /*<<< orphan*/  WIIMOTE_STATE_IR ; 
 int WM_IR_TYPE_BASIC ; 
 int WM_IR_TYPE_EXTENDED ; 
 int /*<<< orphan*/  WM_REG_IR_MODENUM ; 
 int /*<<< orphan*/  wiiuse_write_data (struct wiimote_t*,int /*<<< orphan*/ ,int*,int,int /*<<< orphan*/ *) ; 

void wiiuse_set_ir_mode(struct wiimote_t *wm)
{
	ubyte buf = 0x00;

	if(!wm) return;
	if(!WIIMOTE_IS_SET(wm,WIIMOTE_STATE_IR)) return;

	if(WIIMOTE_IS_SET(wm,WIIMOTE_STATE_EXP)) buf = WM_IR_TYPE_BASIC;
	else buf = WM_IR_TYPE_EXTENDED;
	wiiuse_write_data(wm,WM_REG_IR_MODENUM, &buf, 1, NULL);
}