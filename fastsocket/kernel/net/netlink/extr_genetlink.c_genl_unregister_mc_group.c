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
struct genl_multicast_group {int dummy; } ;
struct genl_family {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  __genl_unregister_mc_group (struct genl_family*,struct genl_multicast_group*) ; 
 int /*<<< orphan*/  genl_lock () ; 
 int /*<<< orphan*/  genl_unlock () ; 

void genl_unregister_mc_group(struct genl_family *family,
			      struct genl_multicast_group *grp)
{
	genl_lock();
	__genl_unregister_mc_group(family, grp);
	genl_unlock();
}