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
struct TYPE_4__ {scalar_t__ pad; int /*<<< orphan*/  fork_type; void* start_block; void* cnid; } ;
struct TYPE_5__ {TYPE_1__ ext; int /*<<< orphan*/  key_len; } ;
typedef  TYPE_2__ hfsplus_btree_key ;

/* Variables and functions */
 scalar_t__ HFSPLUS_EXT_KEYLEN ; 
 int /*<<< orphan*/  cpu_to_be16 (scalar_t__) ; 
 void* cpu_to_be32 (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void hfsplus_ext_build_key(hfsplus_btree_key *key, u32 cnid,
				  u32 block, u8 type)
{
	key->key_len = cpu_to_be16(HFSPLUS_EXT_KEYLEN - 2);
	key->ext.cnid = cpu_to_be32(cnid);
	key->ext.start_block = cpu_to_be32(block);
	key->ext.fork_type = type;
	key->ext.pad = 0;
}