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
struct rds_iw_device {int /*<<< orphan*/  spinlock; int /*<<< orphan*/  conn_list; } ;

/* Variables and functions */
 int /*<<< orphan*/  __rds_iw_destroy_conns (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static inline void rds_iw_destroy_conns(struct rds_iw_device *rds_iwdev)
{
	__rds_iw_destroy_conns(&rds_iwdev->conn_list, &rds_iwdev->spinlock);
}