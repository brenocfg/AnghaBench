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

__attribute__((used)) static int boundary_lt(unsigned int a, int adir,
		       unsigned int b, int bdir)
{
	if (adir < 0) {
		a--;
		adir = 1;
	} else if (adir > 0)
		adir = 1;
	if (bdir < 0) {
		b--;
		bdir = 1;
	} else if (bdir > 0)
		bdir = 1;
	return a < b || (a == b && adir < bdir);
}