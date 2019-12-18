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
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int /*<<< orphan*/  bi_rw; scalar_t__ bi_bdev; } ;
struct mapped_device {scalar_t__ queue; TYPE_1__* disk; int /*<<< orphan*/  wq; TYPE_3__ flush_bio; scalar_t__ bdev; int /*<<< orphan*/  name; int /*<<< orphan*/  eventq; int /*<<< orphan*/  work; int /*<<< orphan*/  wait; int /*<<< orphan*/ * pending; int /*<<< orphan*/  uevent_lock; int /*<<< orphan*/  uevent_list; int /*<<< orphan*/  uevent_seq; int /*<<< orphan*/  event_nr; int /*<<< orphan*/  open_count; int /*<<< orphan*/  holders; int /*<<< orphan*/  map_lock; int /*<<< orphan*/  deferred_lock; int /*<<< orphan*/  type_lock; int /*<<< orphan*/  suspend_lock; int /*<<< orphan*/  io_lock; int /*<<< orphan*/  type; } ;
struct TYPE_7__ {int first_minor; int /*<<< orphan*/  disk_name; struct mapped_device* private_data; scalar_t__ queue; int /*<<< orphan*/ * fops; int /*<<< orphan*/  major; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int /*<<< orphan*/  DMWARN (char*) ; 
 int DM_ANY_MINOR ; 
 int /*<<< orphan*/  DM_TYPE_NONE ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  INIT_WORK (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 void* MINOR_ALLOCED ; 
 int /*<<< orphan*/  MKDEV (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  THIS_MODULE ; 
 int /*<<< orphan*/  WRITE_FLUSH ; 
 int /*<<< orphan*/  _major ; 
 int /*<<< orphan*/  _minor_idr ; 
 int /*<<< orphan*/  _minor_lock ; 
 int /*<<< orphan*/  add_disk (TYPE_1__*) ; 
 TYPE_1__* alloc_disk (int) ; 
 int /*<<< orphan*/  atomic_set (int /*<<< orphan*/ *,int) ; 
 scalar_t__ bdget_disk (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bio_init (TYPE_3__*) ; 
 scalar_t__ blk_alloc_queue (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  blk_cleanup_queue (scalar_t__) ; 
 int /*<<< orphan*/  create_singlethread_workqueue (char*) ; 
 int /*<<< orphan*/  del_gendisk (TYPE_1__*) ; 
 int /*<<< orphan*/  destroy_workqueue (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dm_blk_dops ; 
 int /*<<< orphan*/  dm_init_md_queue (struct mapped_device*) ; 
 int /*<<< orphan*/  dm_wq_work ; 
 int /*<<< orphan*/  format_dev_t (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free_minor (int) ; 
 void* idr_replace (int /*<<< orphan*/ *,struct mapped_device*,int) ; 
 int /*<<< orphan*/  init_rwsem (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  init_waitqueue_head (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kfree (struct mapped_device*) ; 
 struct mapped_device* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  module_put (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 
 int next_free_minor (int*) ; 
 int /*<<< orphan*/  put_disk (TYPE_1__*) ; 
 int /*<<< orphan*/  rwlock_init (int /*<<< orphan*/ *) ; 
 int specific_minor (int) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sprintf (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  try_module_get (int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct mapped_device *alloc_dev(int minor)
{
	int r;
	struct mapped_device *md = kzalloc(sizeof(*md), GFP_KERNEL);
	void *old_md;

	if (!md) {
		DMWARN("unable to allocate device, out of memory.");
		return NULL;
	}

	if (!try_module_get(THIS_MODULE))
		goto bad_module_get;

	/* get a minor number for the dev */
	if (minor == DM_ANY_MINOR)
		r = next_free_minor(&minor);
	else
		r = specific_minor(minor);
	if (r < 0)
		goto bad_minor;

	md->type = DM_TYPE_NONE;
	init_rwsem(&md->io_lock);
	mutex_init(&md->suspend_lock);
	mutex_init(&md->type_lock);
	spin_lock_init(&md->deferred_lock);
	rwlock_init(&md->map_lock);
	atomic_set(&md->holders, 1);
	atomic_set(&md->open_count, 0);
	atomic_set(&md->event_nr, 0);
	atomic_set(&md->uevent_seq, 0);
	INIT_LIST_HEAD(&md->uevent_list);
	spin_lock_init(&md->uevent_lock);

	md->queue = blk_alloc_queue(GFP_KERNEL);
	if (!md->queue)
		goto bad_queue;

	dm_init_md_queue(md);

	md->disk = alloc_disk(1);
	if (!md->disk)
		goto bad_disk;

	atomic_set(&md->pending[0], 0);
	atomic_set(&md->pending[1], 0);
	init_waitqueue_head(&md->wait);
	INIT_WORK(&md->work, dm_wq_work);
	init_waitqueue_head(&md->eventq);

	md->disk->major = _major;
	md->disk->first_minor = minor;
	md->disk->fops = &dm_blk_dops;
	md->disk->queue = md->queue;
	md->disk->private_data = md;
	sprintf(md->disk->disk_name, "dm-%d", minor);
	add_disk(md->disk);
	format_dev_t(md->name, MKDEV(_major, minor));

	md->wq = create_singlethread_workqueue("kdmflush");
	if (!md->wq)
		goto bad_thread;

	md->bdev = bdget_disk(md->disk, 0);
	if (!md->bdev)
		goto bad_bdev;

	bio_init(&md->flush_bio);
	md->flush_bio.bi_bdev = md->bdev;
	md->flush_bio.bi_rw = WRITE_FLUSH;

	/* Populate the mapping, nobody knows we exist yet */
	spin_lock(&_minor_lock);
	old_md = idr_replace(&_minor_idr, md, minor);
	spin_unlock(&_minor_lock);

	BUG_ON(old_md != MINOR_ALLOCED);

	return md;

bad_bdev:
	destroy_workqueue(md->wq);
bad_thread:
	del_gendisk(md->disk);
	put_disk(md->disk);
bad_disk:
	blk_cleanup_queue(md->queue);
bad_queue:
	free_minor(minor);
bad_minor:
	module_put(THIS_MODULE);
bad_module_get:
	kfree(md);
	return NULL;
}