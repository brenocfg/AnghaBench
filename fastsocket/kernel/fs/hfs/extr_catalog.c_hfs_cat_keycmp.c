#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int /*<<< orphan*/  len; int /*<<< orphan*/  name; } ;
struct TYPE_6__ {TYPE_2__ CName; int /*<<< orphan*/  ParID; } ;
struct TYPE_8__ {TYPE_1__ cat; } ;
typedef  TYPE_3__ btree_key ;

/* Variables and functions */
 int be32_to_cpu (int /*<<< orphan*/ ) ; 
 int hfs_strcmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int hfs_cat_keycmp(const btree_key *key1, const btree_key *key2)
{
	int retval;

	retval = be32_to_cpu(key1->cat.ParID) - be32_to_cpu(key2->cat.ParID);
	if (!retval)
		retval = hfs_strcmp(key1->cat.CName.name, key1->cat.CName.len,
				    key2->cat.CName.name, key2->cat.CName.len);

	return retval;
}