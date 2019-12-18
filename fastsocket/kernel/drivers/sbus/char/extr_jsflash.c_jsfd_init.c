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
struct jsflash {scalar_t__ base; struct jsfd_part* dv; } ;
struct jsfd_part {int dsize; } ;
struct gendisk {int first_minor; scalar_t__ queue; struct jsfd_part* private_data; int /*<<< orphan*/ * fops; int /*<<< orphan*/  disk_name; int /*<<< orphan*/  major; } ;
typedef  int /*<<< orphan*/  DEFINE_SPINLOCK ;

/* Variables and functions */
 int EIO ; 
 int ENOMEM ; 
 int ENXIO ; 
 int /*<<< orphan*/  JSFD_MAJOR ; 
 int JSF_MAX ; 
 int JSF_NPART ; 
 int JSF_PART_MASK ; 
 int /*<<< orphan*/  add_disk (struct gendisk*) ; 
 struct gendisk* alloc_disk (int) ; 
 scalar_t__ blk_init_queue (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 struct jsflash jsf0 ; 
 scalar_t__ jsf_queue ; 
 struct gendisk** jsfd_disk ; 
 int /*<<< orphan*/  jsfd_do_request ; 
 int /*<<< orphan*/  jsfd_fops ; 
 int /*<<< orphan*/  put_disk (struct gendisk*) ; 
 scalar_t__ register_blkdev (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  set_capacity (struct gendisk*,int) ; 
 int /*<<< orphan*/  set_disk_ro (struct gendisk*,int) ; 
 int /*<<< orphan*/  sprintf (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  unregister_blkdev (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static int jsfd_init(void)
{
	static DEFINE_SPINLOCK(lock);
	struct jsflash *jsf;
	struct jsfd_part *jdp;
	int err;
	int i;

	if (jsf0.base == 0)
		return -ENXIO;

	err = -ENOMEM;
	for (i = 0; i < JSF_MAX; i++) {
		struct gendisk *disk = alloc_disk(1);
		if (!disk)
			goto out;
		jsfd_disk[i] = disk;
	}

	if (register_blkdev(JSFD_MAJOR, "jsfd")) {
		err = -EIO;
		goto out;
	}

	jsf_queue = blk_init_queue(jsfd_do_request, &lock);
	if (!jsf_queue) {
		err = -ENOMEM;
		unregister_blkdev(JSFD_MAJOR, "jsfd");
		goto out;
	}

	for (i = 0; i < JSF_MAX; i++) {
		struct gendisk *disk = jsfd_disk[i];
		if ((i & JSF_PART_MASK) >= JSF_NPART) continue;
		jsf = &jsf0;	/* actually, &jsfv[i >> JSF_PART_BITS] */
		jdp = &jsf->dv[i&JSF_PART_MASK];

		disk->major = JSFD_MAJOR;
		disk->first_minor = i;
		sprintf(disk->disk_name, "jsfd%d", i);
		disk->fops = &jsfd_fops;
		set_capacity(disk, jdp->dsize >> 9);
		disk->private_data = jdp;
		disk->queue = jsf_queue;
		add_disk(disk);
		set_disk_ro(disk, 1);
	}
	return 0;
out:
	while (i--)
		put_disk(jsfd_disk[i]);
	return err;
}