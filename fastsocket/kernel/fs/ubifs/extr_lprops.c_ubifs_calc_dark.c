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
struct ubifs_info {int dark_wm; } ;

/* Variables and functions */
 int MIN_WRITE_SZ ; 
 int /*<<< orphan*/  ubifs_assert (int) ; 

int ubifs_calc_dark(const struct ubifs_info *c, int spc)
{
	ubifs_assert(!(spc & 7));

	if (spc < c->dark_wm)
		return spc;

	/*
	 * If we have slightly more space then the dark space watermark, we can
	 * anyway safely assume it we'll be able to write a node of the
	 * smallest size there.
	 */
	if (spc - c->dark_wm < MIN_WRITE_SZ)
		return spc - MIN_WRITE_SZ;

	return c->dark_wm;
}