#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  event ;
struct TYPE_3__ {scalar_t__ pressure; int x; int y; } ;
typedef  TYPE_1__ UCB1X00_TS_EVENT ;

/* Variables and functions */
 int /*<<< orphan*/  perror (char*) ; 
 int read (scalar_t__,TYPE_1__*,int) ; 
 int* touchcal ; 
 scalar_t__ touchdev ; 

int gp2x_touchpad_read(int *x, int *y)
{
	UCB1X00_TS_EVENT event;
	static int zero_seen = 0;
	int retval;

	if (touchdev < 0) return -1;

	retval = read(touchdev, &event, sizeof(event));
	if (retval <= 0) {
		perror("touch read failed");
		return -1;
	}
	// this is to ignore the messed-up 4.1.x driver
	if (event.pressure == 0) zero_seen = 1;

	if (x) *x = (event.x * touchcal[0] + touchcal[2]) >> 16;
	if (y) *y = (event.y * touchcal[4] + touchcal[5]) >> 16;
	// printf("read %i %i %i\n", event.pressure, *x, *y);

	return zero_seen ? event.pressure : 0;
}