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
typedef  int /*<<< orphan*/  u32 ;
struct super_block {int dummy; } ;
struct qstr {int dummy; } ;
struct hfs_name {int dummy; } ;
struct TYPE_8__ {int len; } ;
struct TYPE_6__ {TYPE_3__ CName; int /*<<< orphan*/  ParID; scalar_t__ reserved; } ;
struct TYPE_7__ {int key_len; TYPE_1__ cat; } ;
typedef  TYPE_2__ btree_key ;

/* Variables and functions */
 int /*<<< orphan*/  cpu_to_be32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hfs_asc2mac (struct super_block*,TYPE_3__*,struct qstr*) ; 
 int /*<<< orphan*/  memset (TYPE_3__*,int /*<<< orphan*/ ,int) ; 

void hfs_cat_build_key(struct super_block *sb, btree_key *key, u32 parent, struct qstr *name)
{
	key->cat.reserved = 0;
	key->cat.ParID = cpu_to_be32(parent);
	if (name) {
		hfs_asc2mac(sb, &key->cat.CName, name);
		key->key_len = 6 + key->cat.CName.len;
	} else {
		memset(&key->cat.CName, 0, sizeof(struct hfs_name));
		key->key_len = 6;
	}
}