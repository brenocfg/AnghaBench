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
struct rds_info_iterator {int /*<<< orphan*/ * addr; } ;

/* Variables and functions */
 int /*<<< orphan*/  KM_USER0 ; 
 int /*<<< orphan*/  kunmap_atomic (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

void rds_info_iter_unmap(struct rds_info_iterator *iter)
{
	if (iter->addr) {
		kunmap_atomic(iter->addr, KM_USER0);
		iter->addr = NULL;
	}
}