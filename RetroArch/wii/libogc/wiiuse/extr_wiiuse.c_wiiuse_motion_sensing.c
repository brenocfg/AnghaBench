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
struct wiimote_t {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  WIIMOTE_DISABLE_STATE (struct wiimote_t*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WIIMOTE_ENABLE_STATE (struct wiimote_t*,int /*<<< orphan*/ ) ; 
 scalar_t__ WIIMOTE_IS_SET (struct wiimote_t*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WIIMOTE_STATE_ACC ; 
 int /*<<< orphan*/  WIIMOTE_STATE_HANDSHAKE_COMPLETE ; 
 int /*<<< orphan*/  wiiuse_status (struct wiimote_t*,int /*<<< orphan*/ *) ; 

void wiiuse_motion_sensing(struct wiimote_t* wm, int status)
{
	if (status) {
		if(WIIMOTE_IS_SET(wm,WIIMOTE_STATE_ACC)) return;
		WIIMOTE_ENABLE_STATE(wm, WIIMOTE_STATE_ACC);
	} else {
		if(!WIIMOTE_IS_SET(wm,WIIMOTE_STATE_ACC)) return;
		WIIMOTE_DISABLE_STATE(wm, WIIMOTE_STATE_ACC);
	}

	if(!WIIMOTE_IS_SET(wm,WIIMOTE_STATE_HANDSHAKE_COMPLETE)) return;

	wiiuse_status(wm,NULL);
}