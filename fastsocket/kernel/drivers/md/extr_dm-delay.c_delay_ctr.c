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
struct dm_target {char* error; int num_flush_requests; int num_discard_requests; struct delay_c* private; int /*<<< orphan*/  table; } ;
struct delay_c {unsigned long long start_read; unsigned long long read_delay; unsigned long long start_write; unsigned long long write_delay; int /*<<< orphan*/ * dev_read; int /*<<< orphan*/ * dev_write; int /*<<< orphan*/  may_delay; int /*<<< orphan*/  timer_lock; int /*<<< orphan*/  delayed_bios; int /*<<< orphan*/  flush_expired_bios; int /*<<< orphan*/  delay_timer; int /*<<< orphan*/  delayed_pool; scalar_t__ writes; scalar_t__ reads; } ;

/* Variables and functions */
 int /*<<< orphan*/  DMERR (char*) ; 
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  INIT_WORK (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  atomic_set (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  delayed_cache ; 
 scalar_t__ dm_get_device (struct dm_target*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  dm_put_device (struct dm_target*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dm_table_get_mode (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  flush_expired_bios ; 
 int /*<<< orphan*/  handle_delayed_timer ; 
 int /*<<< orphan*/  kfree (struct delay_c*) ; 
 struct delay_c* kmalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mempool_create_slab_pool (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  setup_timer (int /*<<< orphan*/ *,int /*<<< orphan*/ ,unsigned long) ; 
 int sscanf (char*,char*,unsigned long long*,char*) ; 

__attribute__((used)) static int delay_ctr(struct dm_target *ti, unsigned int argc, char **argv)
{
	struct delay_c *dc;
	unsigned long long tmpll;
	char dummy;

	if (argc != 3 && argc != 6) {
		ti->error = "requires exactly 3 or 6 arguments";
		return -EINVAL;
	}

	dc = kmalloc(sizeof(*dc), GFP_KERNEL);
	if (!dc) {
		ti->error = "Cannot allocate context";
		return -ENOMEM;
	}

	dc->reads = dc->writes = 0;

	if (sscanf(argv[1], "%llu%c", &tmpll, &dummy) != 1) {
		ti->error = "Invalid device sector";
		goto bad;
	}
	dc->start_read = tmpll;

	if (sscanf(argv[2], "%u%c", &dc->read_delay, &dummy) != 1) {
		ti->error = "Invalid delay";
		goto bad;
	}

	if (dm_get_device(ti, argv[0], dm_table_get_mode(ti->table),
			  &dc->dev_read)) {
		ti->error = "Device lookup failed";
		goto bad;
	}

	dc->dev_write = NULL;
	if (argc == 3)
		goto out;

	if (sscanf(argv[4], "%llu%c", &tmpll, &dummy) != 1) {
		ti->error = "Invalid write device sector";
		goto bad_dev_read;
	}
	dc->start_write = tmpll;

	if (sscanf(argv[5], "%u%c", &dc->write_delay, &dummy) != 1) {
		ti->error = "Invalid write delay";
		goto bad_dev_read;
	}

	if (dm_get_device(ti, argv[3], dm_table_get_mode(ti->table),
			  &dc->dev_write)) {
		ti->error = "Write device lookup failed";
		goto bad_dev_read;
	}

out:
	dc->delayed_pool = mempool_create_slab_pool(128, delayed_cache);
	if (!dc->delayed_pool) {
		DMERR("Couldn't create delayed bio pool.");
		goto bad_dev_write;
	}

	setup_timer(&dc->delay_timer, handle_delayed_timer, (unsigned long)dc);

	INIT_WORK(&dc->flush_expired_bios, flush_expired_bios);
	INIT_LIST_HEAD(&dc->delayed_bios);
	mutex_init(&dc->timer_lock);
	atomic_set(&dc->may_delay, 1);

	ti->num_flush_requests = 1;
	ti->num_discard_requests = 1;
	ti->private = dc;
	return 0;

bad_dev_write:
	if (dc->dev_write)
		dm_put_device(ti, dc->dev_write);
bad_dev_read:
	dm_put_device(ti, dc->dev_read);
bad:
	kfree(dc);
	return -EINVAL;
}