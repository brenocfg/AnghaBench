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
struct ubifs_znode {struct ubifs_znode* cnext; int /*<<< orphan*/  flags; } ;
struct ubifs_info {int /*<<< orphan*/  clean_zn_cnt; struct ubifs_znode* cnext; } ;

/* Variables and functions */
 int /*<<< orphan*/  OBSOLETE_ZNODE ; 
 int /*<<< orphan*/  atomic_long_inc (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kfree (struct ubifs_znode*) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ubifs_clean_zn_cnt ; 

__attribute__((used)) static void free_obsolete_znodes(struct ubifs_info *c)
{
	struct ubifs_znode *znode, *cnext;

	cnext = c->cnext;
	do {
		znode = cnext;
		cnext = znode->cnext;
		if (test_bit(OBSOLETE_ZNODE, &znode->flags))
			kfree(znode);
		else {
			znode->cnext = NULL;
			atomic_long_inc(&c->clean_zn_cnt);
			atomic_long_inc(&ubifs_clean_zn_cnt);
		}
	} while (cnext != c->cnext);
}