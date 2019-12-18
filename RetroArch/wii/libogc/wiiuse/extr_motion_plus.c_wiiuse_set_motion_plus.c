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
 int /*<<< orphan*/  WIIMOTE_ENABLE_STATE (struct wiimote_t*,int /*<<< orphan*/ ) ; 
 scalar_t__ WIIMOTE_IS_SET (struct wiimote_t*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WIIMOTE_STATE_EXP_HANDSHAKE ; 
 int /*<<< orphan*/  WM_EXP_MEM_ENABLE1 ; 
 int /*<<< orphan*/  WM_EXP_MOTION_PLUS_ENABLE ; 
 int /*<<< orphan*/  wiiuse_disable_expansion (struct wiimote_t*) ; 
 int /*<<< orphan*/  wiiuse_motion_plus_check ; 
 int /*<<< orphan*/  wiiuse_set_motion_plus_clear1 ; 
 int /*<<< orphan*/  wiiuse_write_data (struct wiimote_t*,int /*<<< orphan*/ ,int*,int,int /*<<< orphan*/ ) ; 

void wiiuse_set_motion_plus(struct wiimote_t *wm, int status)
{
	ubyte val;

	if(WIIMOTE_IS_SET(wm,WIIMOTE_STATE_EXP_HANDSHAKE))
		return;

	WIIMOTE_ENABLE_STATE(wm, WIIMOTE_STATE_EXP_HANDSHAKE);
	if(status)
	{
		val = 0x04;
		wiiuse_write_data(wm,WM_EXP_MOTION_PLUS_ENABLE,&val,1,wiiuse_motion_plus_check);
	}
	else
	{
		wiiuse_disable_expansion(wm);
		val = 0x55;
		wiiuse_write_data(wm,WM_EXP_MEM_ENABLE1,&val,1,wiiuse_set_motion_plus_clear1);
	}
}