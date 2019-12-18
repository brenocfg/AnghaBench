#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
struct TYPE_3__ {size_t primary_reselect; } ;
struct bonding {TYPE_1__ params; } ;
typedef  int /*<<< orphan*/  ssize_t ;
struct TYPE_4__ {char* modename; } ;

/* Variables and functions */
 TYPE_2__* pri_reselect_tbl ; 
 int /*<<< orphan*/  sprintf (char*,char*,char*,size_t) ; 
 struct bonding* to_bond (struct device*) ; 

__attribute__((used)) static ssize_t bonding_show_primary_reselect(struct device *d,
					     struct device_attribute *attr,
					     char *buf)
{
	struct bonding *bond = to_bond(d);

	return sprintf(buf, "%s %d\n",
		       pri_reselect_tbl[bond->params.primary_reselect].modename,
		       bond->params.primary_reselect);
}