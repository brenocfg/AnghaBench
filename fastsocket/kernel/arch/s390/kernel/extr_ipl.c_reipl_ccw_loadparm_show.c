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
struct kobject {int dummy; } ;
struct kobj_attribute {int dummy; } ;
typedef  int /*<<< orphan*/  ssize_t ;

/* Variables and functions */
 int /*<<< orphan*/  reipl_block_ccw ; 
 int /*<<< orphan*/  reipl_generic_loadparm_show (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static ssize_t reipl_ccw_loadparm_show(struct kobject *kobj,
				       struct kobj_attribute *attr, char *page)
{
	return reipl_generic_loadparm_show(reipl_block_ccw, page);
}