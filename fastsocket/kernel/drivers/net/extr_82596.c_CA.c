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
typedef  int /*<<< orphan*/  u32 ;
struct net_device {scalar_t__ base_addr; } ;
struct i596_reg {int ca; } ;

/* Variables and functions */
 scalar_t__ MACH_IS_APRICOT ; 
 scalar_t__ MACH_IS_BVME6000 ; 
 scalar_t__ MACH_IS_MVME16x ; 
 int /*<<< orphan*/  outw (int /*<<< orphan*/ ,short) ; 

__attribute__((used)) static inline void CA(struct net_device *dev)
{
#ifdef ENABLE_MVME16x_NET
	if (MACH_IS_MVME16x) {
		((struct i596_reg *) dev->base_addr)->ca = 1;
	}
#endif
#ifdef ENABLE_BVME6000_NET
	if (MACH_IS_BVME6000) {
		volatile u32 i;

		i = *(volatile u32 *) (dev->base_addr);
	}
#endif
#ifdef ENABLE_APRICOT
	if (MACH_IS_APRICOT) {
		outw(0, (short) (dev->base_addr) + 4);
	}
#endif
}