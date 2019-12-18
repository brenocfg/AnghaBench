#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {void* bt_crtxg; void* bt_txg; void* bt_gen; void* bt_offset; void* bt_dnodesize; void* bt_object; int /*<<< orphan*/  bt_objset; int /*<<< orphan*/  bt_magic; } ;
typedef  TYPE_1__ ztest_block_tag_t ;
typedef  void* uint64_t ;
typedef  int /*<<< orphan*/  objset_t ;

/* Variables and functions */
 int /*<<< orphan*/  BT_MAGIC ; 
 int /*<<< orphan*/  dmu_objset_id (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
ztest_bt_generate(ztest_block_tag_t *bt, objset_t *os, uint64_t object,
    uint64_t dnodesize, uint64_t offset, uint64_t gen, uint64_t txg,
    uint64_t crtxg)
{
	bt->bt_magic = BT_MAGIC;
	bt->bt_objset = dmu_objset_id(os);
	bt->bt_object = object;
	bt->bt_dnodesize = dnodesize;
	bt->bt_offset = offset;
	bt->bt_gen = gen;
	bt->bt_txg = txg;
	bt->bt_crtxg = crtxg;
}