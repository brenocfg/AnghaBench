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

/* Variables and functions */
 int merisc_board_id ; 

const char *merisc_revision(void)
{
	switch (merisc_board_id) {
	case 0:
		return "B";
	case 1:
		return "D";
	case 2:
		return "A";
	default:
		return "Unknown";
	}
}