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
struct pxafb_info {int /*<<< orphan*/  clk; } ;

/* Variables and functions */
 int clk_get_rate (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  do_div (unsigned long long,int) ; 

__attribute__((used)) static inline unsigned int get_pcd(struct pxafb_info *fbi,
				   unsigned int pixclock)
{
	unsigned long long pcd;

	/* FIXME: Need to take into account Double Pixel Clock mode
	 * (DPC) bit? or perhaps set it based on the various clock
	 * speeds */
	pcd = (unsigned long long)(clk_get_rate(fbi->clk) / 10000);
	pcd *= pixclock;
	do_div(pcd, 100000000 * 2);
	/* no need for this, since we should subtract 1 anyway. they cancel */
	/* pcd += 1; */ /* make up for integer math truncations */
	return (unsigned int)pcd;
}