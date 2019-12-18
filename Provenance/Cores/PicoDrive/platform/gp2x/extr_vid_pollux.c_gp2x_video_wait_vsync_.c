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
 int* memregl ; 
 int /*<<< orphan*/  spend_cycles (int) ; 

__attribute__((used)) static void gp2x_video_wait_vsync_(void)
{
	while (!(memregl[0x308c>>2] & (1 << 10)))
		spend_cycles(128);
	memregl[0x308c>>2] |= 1 << 10;
}