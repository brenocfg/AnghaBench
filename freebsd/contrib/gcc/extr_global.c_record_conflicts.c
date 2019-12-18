#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int /*<<< orphan*/  hard_reg_conflicts; } ;

/* Variables and functions */
 int /*<<< orphan*/  IOR_HARD_REG_SET (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_1__* allocno ; 
 int /*<<< orphan*/  hard_regs_live ; 

__attribute__((used)) static void
record_conflicts (int *allocno_vec, int len)
{
  while (--len >= 0)
    IOR_HARD_REG_SET (allocno[allocno_vec[len]].hard_reg_conflicts,
                      hard_regs_live);
}