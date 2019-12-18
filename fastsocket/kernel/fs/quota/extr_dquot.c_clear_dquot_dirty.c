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
struct dquot {int /*<<< orphan*/  dq_dirty; int /*<<< orphan*/  dq_flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  DQ_MOD_B ; 
 int /*<<< orphan*/  list_del_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  test_and_clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static inline int clear_dquot_dirty(struct dquot *dquot)
{
	if (!test_and_clear_bit(DQ_MOD_B, &dquot->dq_flags))
		return 0;
	list_del_init(&dquot->dq_dirty);
	return 1;
}