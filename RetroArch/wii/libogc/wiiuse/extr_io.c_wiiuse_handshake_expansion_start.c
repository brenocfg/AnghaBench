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
struct wiimote_t {scalar_t__ expansion_state; } ;

/* Variables and functions */
 int /*<<< orphan*/  WIIMOTE_ENABLE_STATE (struct wiimote_t*,int /*<<< orphan*/ ) ; 
 scalar_t__ WIIMOTE_IS_SET (struct wiimote_t*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WIIMOTE_STATE_EXP ; 
 int /*<<< orphan*/  WIIMOTE_STATE_EXP_FAILED ; 
 int /*<<< orphan*/  WIIMOTE_STATE_EXP_HANDSHAKE ; 
 int /*<<< orphan*/  wiiuse_handshake_expansion (struct wiimote_t*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

void wiiuse_handshake_expansion_start(struct wiimote_t *wm)
{
	if(WIIMOTE_IS_SET(wm,WIIMOTE_STATE_EXP) || WIIMOTE_IS_SET(wm,WIIMOTE_STATE_EXP_FAILED) || WIIMOTE_IS_SET(wm,WIIMOTE_STATE_EXP_HANDSHAKE))
		return;

	wm->expansion_state = 0;
	WIIMOTE_ENABLE_STATE(wm, WIIMOTE_STATE_EXP_HANDSHAKE);
	wiiuse_handshake_expansion(wm, NULL, 0);
}