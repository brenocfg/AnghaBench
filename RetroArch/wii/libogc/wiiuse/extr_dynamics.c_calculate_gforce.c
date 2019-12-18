#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct vec3w_t {scalar_t__ z; scalar_t__ y; scalar_t__ x; } ;
struct gforce_t {float x; float y; float z; } ;
struct TYPE_4__ {scalar_t__ z; scalar_t__ y; scalar_t__ x; } ;
struct TYPE_3__ {scalar_t__ z; scalar_t__ y; scalar_t__ x; } ;
struct accel_t {TYPE_2__ cal_zero; TYPE_1__ cal_g; } ;

/* Variables and functions */

void calculate_gforce(struct accel_t* ac, struct vec3w_t* accel, struct gforce_t* gforce) {
	float xg, yg, zg;

	/* find out how much it has to move to be 1g */
	xg = (float)ac->cal_g.x;
	yg = (float)ac->cal_g.y;
	zg = (float)ac->cal_g.z;

	/* find out how much it actually moved and normalize to +/- 1g */
	gforce->x = ((float)accel->x - (float)ac->cal_zero.x) / xg;
	gforce->y = ((float)accel->y - (float)ac->cal_zero.y) / yg;
	gforce->z = ((float)accel->z - (float)ac->cal_zero.z) / zg;
}