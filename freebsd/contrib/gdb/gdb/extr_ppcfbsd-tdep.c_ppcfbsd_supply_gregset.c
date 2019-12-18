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
struct regset {int dummy; } ;
struct regcache {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ppcfbsd_supply_reg (void*,int) ; 

__attribute__((used)) static void
ppcfbsd_supply_gregset (const struct regset *regset,
			struct regcache *regcache,
			int regnum, void *gregs, size_t size)
{
  ppcfbsd_supply_reg (gregs, -1);
}