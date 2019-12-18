#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;
typedef  int /*<<< orphan*/  u32 ;
typedef  int /*<<< orphan*/  u16 ;
struct TYPE_4__ {int /*<<< orphan*/  FABN; int /*<<< orphan*/  FNum; int /*<<< orphan*/  FkType; } ;
struct TYPE_5__ {int key_len; TYPE_1__ ext; } ;
typedef  TYPE_2__ hfs_btree_key ;

/* Variables and functions */
 int /*<<< orphan*/  cpu_to_be16 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cpu_to_be32 (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void hfs_ext_build_key(hfs_btree_key *key, u32 cnid, u16 block, u8 type)
{
	key->key_len = 7;
	key->ext.FkType = type;
	key->ext.FNum = cpu_to_be32(cnid);
	key->ext.FABN = cpu_to_be16(block);
}