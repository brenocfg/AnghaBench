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
typedef  int /*<<< orphan*/  unw_word_t ;
typedef  int u64 ;
struct regs_dump {int /*<<< orphan*/ * regs; } ;

/* Variables and functions */
 int EINVAL ; 

__attribute__((used)) static int reg_value(unw_word_t *valp, struct regs_dump *regs, int id,
		     u64 sample_regs)
{
	int i, idx = 0;

	if (!(sample_regs & (1 << id)))
		return -EINVAL;

	for (i = 0; i < id; i++) {
		if (sample_regs & (1 << i))
			idx++;
	}

	*valp = regs->regs[idx];
	return 0;
}