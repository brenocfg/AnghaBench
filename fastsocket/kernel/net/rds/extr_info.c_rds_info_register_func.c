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
typedef  int rds_info_func ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int RDS_INFO_FIRST ; 
 int RDS_INFO_LAST ; 
 int* rds_info_funcs ; 
 int /*<<< orphan*/  rds_info_lock ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

void rds_info_register_func(int optname, rds_info_func func)
{
	int offset = optname - RDS_INFO_FIRST;

	BUG_ON(optname < RDS_INFO_FIRST || optname > RDS_INFO_LAST);

	spin_lock(&rds_info_lock);
	BUG_ON(rds_info_funcs[offset]);
	rds_info_funcs[offset] = func;
	spin_unlock(&rds_info_lock);
}