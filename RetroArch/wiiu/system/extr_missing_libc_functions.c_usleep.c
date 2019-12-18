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
typedef  int /*<<< orphan*/  useconds_t ;

/* Variables and functions */
 int /*<<< orphan*/  OSSleepTicks (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  us_to_ticks (int /*<<< orphan*/ ) ; 

int usleep(useconds_t microseconds) {
	OSSleepTicks(us_to_ticks(microseconds));
	return 0;
}