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
struct s6i2c_if {unsigned int reg; } ;

/* Variables and functions */
 int /*<<< orphan*/  readl (unsigned int) ; 

__attribute__((used)) static inline u32 i2c_rd32(struct s6i2c_if *iface, unsigned n)
{
	return readl(iface->reg + (n));
}