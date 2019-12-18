#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct ubd {TYPE_4__* queue; int /*<<< orphan*/  size; int /*<<< orphan*/  lock; int /*<<< orphan*/  sg; int /*<<< orphan*/  restart; int /*<<< orphan*/ * file; } ;
struct TYPE_8__ {struct ubd* queuedata; } ;
struct TYPE_7__ {int /*<<< orphan*/  disk_name; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  MAX_SG ; 
 int /*<<< orphan*/  ROUND_BLOCK (int /*<<< orphan*/ ) ; 
 scalar_t__ UBD_MAJOR ; 
 int /*<<< orphan*/  blk_cleanup_queue (TYPE_4__*) ; 
 TYPE_4__* blk_init_queue (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  blk_queue_max_segments (TYPE_4__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  do_ubd_request ; 
 TYPE_1__** fake_gendisk ; 
 scalar_t__ fake_ide ; 
 scalar_t__ fake_major ; 
 int /*<<< orphan*/  make_ide_entries (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sg_init_table (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct ubd* ubd_devs ; 
 int ubd_disk_register (scalar_t__,int /*<<< orphan*/ ,int,TYPE_1__**) ; 
 int ubd_file_size (struct ubd*,int /*<<< orphan*/ *) ; 
 TYPE_1__** ubd_gendisk ; 

__attribute__((used)) static int ubd_add(int n, char **error_out)
{
	struct ubd *ubd_dev = &ubd_devs[n];
	int err = 0;

	if(ubd_dev->file == NULL)
		goto out;

	err = ubd_file_size(ubd_dev, &ubd_dev->size);
	if(err < 0){
		*error_out = "Couldn't determine size of device's file";
		goto out;
	}

	ubd_dev->size = ROUND_BLOCK(ubd_dev->size);

	INIT_LIST_HEAD(&ubd_dev->restart);
	sg_init_table(ubd_dev->sg, MAX_SG);

	err = -ENOMEM;
	ubd_dev->queue = blk_init_queue(do_ubd_request, &ubd_dev->lock);
	if (ubd_dev->queue == NULL) {
		*error_out = "Failed to initialize device queue";
		goto out;
	}
	ubd_dev->queue->queuedata = ubd_dev;

	blk_queue_max_segments(ubd_dev->queue, MAX_SG);
	err = ubd_disk_register(UBD_MAJOR, ubd_dev->size, n, &ubd_gendisk[n]);
	if(err){
		*error_out = "Failed to register device";
		goto out_cleanup;
	}

	if (fake_major != UBD_MAJOR)
		ubd_disk_register(fake_major, ubd_dev->size, n,
				  &fake_gendisk[n]);

	/*
	 * Perhaps this should also be under the "if (fake_major)" above
	 * using the fake_disk->disk_name
	 */
	if (fake_ide)
		make_ide_entries(ubd_gendisk[n]->disk_name);

	err = 0;
out:
	return err;

out_cleanup:
	blk_cleanup_queue(ubd_dev->queue);
	goto out;
}