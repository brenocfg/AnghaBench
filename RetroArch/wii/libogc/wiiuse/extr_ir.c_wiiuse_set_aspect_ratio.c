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
struct TYPE_2__ {int aspect; int /*<<< orphan*/  pos; int /*<<< orphan*/ * vres; } ;
struct wiimote_t {TYPE_1__ ir; } ;
typedef  enum aspect_t { ____Placeholder_aspect_t } aspect_t ;

/* Variables and functions */
 int WIIUSE_ASPECT_4_3 ; 
 int /*<<< orphan*/  WM_ASPECT_16_9_X ; 
 int /*<<< orphan*/  WM_ASPECT_16_9_Y ; 
 int /*<<< orphan*/  WM_ASPECT_4_3_X ; 
 int /*<<< orphan*/  WM_ASPECT_4_3_Y ; 
 int /*<<< orphan*/  wiiuse_set_ir_position (struct wiimote_t*,int /*<<< orphan*/ ) ; 

void wiiuse_set_aspect_ratio(struct wiimote_t* wm, enum aspect_t aspect) {
	if (!wm)	return;

	wm->ir.aspect = aspect;

	if (aspect == WIIUSE_ASPECT_4_3) {
		wm->ir.vres[0] = WM_ASPECT_4_3_X;
		wm->ir.vres[1] = WM_ASPECT_4_3_Y;
	} else {
		wm->ir.vres[0] = WM_ASPECT_16_9_X;
		wm->ir.vres[1] = WM_ASPECT_16_9_Y;
	}

	/* reset the position offsets */
	wiiuse_set_ir_position(wm, wm->ir.pos);
}