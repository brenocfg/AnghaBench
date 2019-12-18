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
typedef  int u32 ;
struct idt77252_dev {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  SAR_REG_STAT ; 
 int SAR_STAT_CMDBZ ; 
 int readl (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
waitfor_idle(struct idt77252_dev *card)
{
	u32 stat;

	stat = readl(SAR_REG_STAT);
	while (stat & SAR_STAT_CMDBZ)
		stat = readl(SAR_REG_STAT);
}