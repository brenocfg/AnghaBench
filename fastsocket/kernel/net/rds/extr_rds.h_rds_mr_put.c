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
struct rds_mr {int /*<<< orphan*/  r_refcount; } ;

/* Variables and functions */
 int /*<<< orphan*/  __rds_put_mr_final (struct rds_mr*) ; 
 scalar_t__ atomic_dec_and_test (int /*<<< orphan*/ *) ; 

__attribute__((used)) static inline void rds_mr_put(struct rds_mr *mr)
{
	if (atomic_dec_and_test(&mr->r_refcount))
		__rds_put_mr_final(mr);
}