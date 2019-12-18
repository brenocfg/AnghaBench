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
struct lanai_dev {scalar_t__ base; } ;
typedef  enum lanai_register { ____Placeholder_lanai_register } lanai_register ;

/* Variables and functions */
 int /*<<< orphan*/  RWDEBUG (char*,unsigned int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  reg_addr (struct lanai_dev const*,int) ; 
 int /*<<< orphan*/  writel (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline void reg_write(const struct lanai_dev *lanai, u32 val,
	enum lanai_register reg)
{
	RWDEBUG("W [0x%08X] 0x%02X < 0x%08X\n", (unsigned int) lanai->base,
	    (int) reg, val);
	writel(val, reg_addr(lanai, reg));
}