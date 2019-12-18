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
typedef  int /*<<< orphan*/  zfs_deleg_who_type_t ;
struct TYPE_3__ {int /*<<< orphan*/  who_name; int /*<<< orphan*/  who_type; } ;
struct TYPE_4__ {TYPE_1__ who_perm; } ;
typedef  TYPE_2__ who_perm_node_t ;

/* Variables and functions */
 scalar_t__ ZFS_MAX_DELEG_NAME ; 
 int strncmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 
 int who_type2weight (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
who_perm_compare(const void *larg, const void *rarg, void *unused)
{
	const who_perm_node_t *l = larg;
	const who_perm_node_t *r = rarg;
	zfs_deleg_who_type_t ltype = l->who_perm.who_type;
	zfs_deleg_who_type_t rtype = r->who_perm.who_type;
	int lweight = who_type2weight(ltype);
	int rweight = who_type2weight(rtype);
	int res = lweight - rweight;
	if (res == 0)
		res = strncmp(l->who_perm.who_name, r->who_perm.who_name,
		    ZFS_MAX_DELEG_NAME-1);

	if (res == 0)
		return (0);
	if (res > 0)
		return (1);
	else
		return (-1);
}