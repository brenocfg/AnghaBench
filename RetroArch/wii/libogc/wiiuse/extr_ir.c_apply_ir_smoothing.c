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
struct ir_t {scalar_t__ ax; scalar_t__ ay; scalar_t__ sx; scalar_t__ sy; } ;
typedef  scalar_t__ f32 ;

/* Variables and functions */
 scalar_t__ SMOOTH_IR_DEADZONE ; 
 scalar_t__ SMOOTH_IR_RADIUS ; 
 scalar_t__ SMOOTH_IR_SPEED ; 
 int /*<<< orphan*/  WIIUSE_DEBUG (char*,...) ; 
 scalar_t__ atan2f (scalar_t__,scalar_t__) ; 
 scalar_t__ cosf (scalar_t__) ; 
 scalar_t__ sinf (scalar_t__) ; 
 scalar_t__ sqrtf (scalar_t__) ; 

void apply_ir_smoothing(struct ir_t *ir) {
	f32 dx, dy, d, theta;

	WIIUSE_DEBUG("Smooth: OK (%.02f, %.02f) LAST (%.02f, %.02f) ", ir->ax, ir->ay, ir->sx, ir->sy);
	dx = ir->ax - ir->sx;
	dy = ir->ay - ir->sy;
	d = sqrtf(dx*dx + dy*dy);
	if (d > SMOOTH_IR_DEADZONE) {
		if (d < SMOOTH_IR_RADIUS) {
			WIIUSE_DEBUG("INSIDE\n");
			ir->sx += dx * SMOOTH_IR_SPEED;
			ir->sy += dy * SMOOTH_IR_SPEED;
		} else {
			WIIUSE_DEBUG("OUTSIDE\n");
			theta = atan2f(dy, dx);
			ir->sx = ir->ax - cosf(theta) * SMOOTH_IR_RADIUS;
			ir->sy = ir->ay - sinf(theta) * SMOOTH_IR_RADIUS;
		}
	} else {
		WIIUSE_DEBUG("DEADZONE\n");
	}
}