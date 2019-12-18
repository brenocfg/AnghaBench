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
struct dquot {int /*<<< orphan*/  dq_count; } ;

/* Variables and functions */
 int atomic_read (int /*<<< orphan*/ *) ; 

__attribute__((used)) static inline int dqput_blocks(struct dquot *dquot)
{
	if (atomic_read(&dquot->dq_count) <= 1)
		return 1;
	return 0;
}