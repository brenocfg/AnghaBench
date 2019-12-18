#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int is_iodone; struct btrfsic_dev_state* dev_state; } ;
struct btrfsic_dev_state {char* name; TYPE_1__ dummy_block_for_bio_bh_flush; scalar_t__ last_flush_gen; int /*<<< orphan*/  collision_resolving_node; int /*<<< orphan*/ * state; int /*<<< orphan*/ * bdev; int /*<<< orphan*/  magic_num; } ;

/* Variables and functions */
 int /*<<< orphan*/  BTRFSIC_DEV2STATE_MAGIC_NUMBER ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  btrfsic_block_init (TYPE_1__*) ; 

__attribute__((used)) static void btrfsic_dev_state_init(struct btrfsic_dev_state *ds)
{
	ds->magic_num = BTRFSIC_DEV2STATE_MAGIC_NUMBER;
	ds->bdev = NULL;
	ds->state = NULL;
	ds->name[0] = '\0';
	INIT_LIST_HEAD(&ds->collision_resolving_node);
	ds->last_flush_gen = 0;
	btrfsic_block_init(&ds->dummy_block_for_bio_bh_flush);
	ds->dummy_block_for_bio_bh_flush.is_iodone = 1;
	ds->dummy_block_for_bio_bh_flush.dev_state = ds;
}