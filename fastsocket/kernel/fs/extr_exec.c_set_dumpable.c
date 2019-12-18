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
struct mm_struct {int /*<<< orphan*/  flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  MMF_DUMPABLE ; 
 int /*<<< orphan*/  MMF_DUMP_SECURELY ; 
 int /*<<< orphan*/  clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  smp_wmb () ; 

void set_dumpable(struct mm_struct *mm, int value)
{
	switch (value) {
	case 0:
		clear_bit(MMF_DUMPABLE, &mm->flags);
		smp_wmb();
		clear_bit(MMF_DUMP_SECURELY, &mm->flags);
		break;
	case 1:
		set_bit(MMF_DUMPABLE, &mm->flags);
		smp_wmb();
		clear_bit(MMF_DUMP_SECURELY, &mm->flags);
		break;
	case 2:
		set_bit(MMF_DUMP_SECURELY, &mm->flags);
		smp_wmb();
		set_bit(MMF_DUMPABLE, &mm->flags);
		break;
	}
}