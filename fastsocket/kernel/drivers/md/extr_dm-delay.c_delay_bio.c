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
struct dm_delay_info {unsigned long expires; int /*<<< orphan*/  list; struct bio* bio; struct delay_c* context; } ;
struct delay_c {int /*<<< orphan*/  delayed_bios; int /*<<< orphan*/  reads; int /*<<< orphan*/  writes; int /*<<< orphan*/  delayed_pool; int /*<<< orphan*/  may_delay; } ;
struct bio {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_NOIO ; 
 int HZ ; 
 scalar_t__ WRITE ; 
 int /*<<< orphan*/  atomic_read (int /*<<< orphan*/ *) ; 
 scalar_t__ bio_data_dir (struct bio*) ; 
 int /*<<< orphan*/  delayed_bios_lock ; 
 int jiffies ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 struct dm_delay_info* mempool_alloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  queue_timeout (struct delay_c*,unsigned long) ; 

__attribute__((used)) static int delay_bio(struct delay_c *dc, int delay, struct bio *bio)
{
	struct dm_delay_info *delayed;
	unsigned long expires = 0;

	if (!delay || !atomic_read(&dc->may_delay))
		return 1;

	delayed = mempool_alloc(dc->delayed_pool, GFP_NOIO);

	delayed->context = dc;
	delayed->bio = bio;
	delayed->expires = expires = jiffies + (delay * HZ / 1000);

	mutex_lock(&delayed_bios_lock);

	if (bio_data_dir(bio) == WRITE)
		dc->writes++;
	else
		dc->reads++;

	list_add_tail(&delayed->list, &dc->delayed_bios);

	mutex_unlock(&delayed_bios_lock);

	queue_timeout(dc, expires);

	return 0;
}