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
struct map_info {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  VPP_PORT ; 
 unsigned long inl (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  outl (unsigned long,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void l440gx_set_vpp(struct map_info *map, int vpp)
{
	unsigned long l;

	l = inl(VPP_PORT);
	if (vpp) {
		l |= 1;
	} else {
		l &= ~1;
	}
	outl(l, VPP_PORT);
}