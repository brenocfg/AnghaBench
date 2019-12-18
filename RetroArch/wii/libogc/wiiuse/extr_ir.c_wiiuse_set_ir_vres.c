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
struct TYPE_2__ {unsigned int* vres; } ;
struct wiimote_t {TYPE_1__ ir; } ;

/* Variables and functions */

void wiiuse_set_ir_vres(struct wiimote_t* wm, unsigned int x, unsigned int y) {
	if (!wm)	return;

	wm->ir.vres[0] = (x-1);
	wm->ir.vres[1] = (y-1);
}