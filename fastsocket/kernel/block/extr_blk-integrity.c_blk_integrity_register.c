#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct gendisk {TYPE_2__* queue; struct blk_integrity* integrity; } ;
struct blk_integrity {int flags; int /*<<< orphan*/  name; int /*<<< orphan*/  tag_size; int /*<<< orphan*/  get_tag_fn; int /*<<< orphan*/  set_tag_fn; int /*<<< orphan*/  tuple_size; int /*<<< orphan*/  verify_fn; int /*<<< orphan*/  generate_fn; int /*<<< orphan*/  sector_size; int /*<<< orphan*/  kobj; } ;
struct TYPE_6__ {int /*<<< orphan*/  kobj; } ;
struct TYPE_4__ {int /*<<< orphan*/  capabilities; } ;
struct TYPE_5__ {TYPE_1__ backing_dev_info; } ;

/* Variables and functions */
 int /*<<< orphan*/  BDI_CAP_STABLE_WRITES ; 
 int /*<<< orphan*/  BUG_ON (int /*<<< orphan*/ ) ; 
 int GFP_KERNEL ; 
 int INTEGRITY_FLAG_READ ; 
 int INTEGRITY_FLAG_WRITE ; 
 int /*<<< orphan*/  KOBJ_ADD ; 
 int __GFP_ZERO ; 
 int /*<<< orphan*/  bi_unsupported_name ; 
 TYPE_3__* disk_to_dev (struct gendisk*) ; 
 int /*<<< orphan*/  integrity_cachep ; 
 int /*<<< orphan*/  integrity_ktype ; 
 struct blk_integrity* kmem_cache_alloc (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  kmem_cache_free (int /*<<< orphan*/ ,struct blk_integrity*) ; 
 scalar_t__ kobject_init_and_add (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,char*,char*) ; 
 int /*<<< orphan*/  kobject_uevent (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mark_tech_preview (char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  queue_logical_block_size (TYPE_2__*) ; 

int blk_integrity_register(struct gendisk *disk, struct blk_integrity *template)
{
	struct blk_integrity *bi;
	static bool seen = false;

	BUG_ON(disk == NULL);

	if (!seen) {
		mark_tech_preview("DIF/DIX support", NULL);
		seen = true;
	}

	if (disk->integrity == NULL) {
		bi = kmem_cache_alloc(integrity_cachep,
				      GFP_KERNEL | __GFP_ZERO);
		if (!bi)
			return -1;

		if (kobject_init_and_add(&bi->kobj, &integrity_ktype,
					 &disk_to_dev(disk)->kobj,
					 "%s", "integrity")) {
			kmem_cache_free(integrity_cachep, bi);
			return -1;
		}

		kobject_uevent(&bi->kobj, KOBJ_ADD);

		bi->flags |= INTEGRITY_FLAG_READ | INTEGRITY_FLAG_WRITE;
		bi->sector_size = queue_logical_block_size(disk->queue);
		disk->integrity = bi;
	} else
		bi = disk->integrity;

	/* Use the provided profile as template */
	if (template != NULL) {
		bi->name = template->name;
		bi->generate_fn = template->generate_fn;
		bi->verify_fn = template->verify_fn;
		bi->tuple_size = template->tuple_size;
		bi->set_tag_fn = template->set_tag_fn;
		bi->get_tag_fn = template->get_tag_fn;
		bi->tag_size = template->tag_size;
	} else
		bi->name = bi_unsupported_name;

	disk->queue->backing_dev_info.capabilities |= BDI_CAP_STABLE_WRITES;

	return 0;
}