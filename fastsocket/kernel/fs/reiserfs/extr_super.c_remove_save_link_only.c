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
struct super_block {int dummy; } ;
struct reiserfs_transaction_handle {int dummy; } ;
struct reiserfs_key {int /*<<< orphan*/  k_objectid; } ;

/* Variables and functions */
 int /*<<< orphan*/  JOURNAL_PER_BALANCE_CNT ; 
 int journal_begin (struct reiserfs_transaction_handle*,struct super_block*,int /*<<< orphan*/ ) ; 
 int journal_end (struct reiserfs_transaction_handle*,struct super_block*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  le32_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  reiserfs_delete_solid_item (struct reiserfs_transaction_handle*,int /*<<< orphan*/ *,struct reiserfs_key*) ; 
 int /*<<< orphan*/  reiserfs_release_objectid (struct reiserfs_transaction_handle*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int remove_save_link_only(struct super_block *s,
				 struct reiserfs_key *key, int oid_free)
{
	struct reiserfs_transaction_handle th;
	int err;

	/* we are going to do one balancing */
	err = journal_begin(&th, s, JOURNAL_PER_BALANCE_CNT);
	if (err)
		return err;

	reiserfs_delete_solid_item(&th, NULL, key);
	if (oid_free)
		/* removals are protected by direct items */
		reiserfs_release_objectid(&th, le32_to_cpu(key->k_objectid));

	return journal_end(&th, s, JOURNAL_PER_BALANCE_CNT);
}