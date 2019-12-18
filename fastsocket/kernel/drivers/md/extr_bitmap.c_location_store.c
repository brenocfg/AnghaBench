#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {long long offset; scalar_t__ external; long long default_offset; struct file* file; } ;
struct mddev {scalar_t__ major_version; int /*<<< orphan*/  thread; int /*<<< orphan*/  flags; int /*<<< orphan*/  external; TYPE_2__* pers; TYPE_1__ bitmap_info; scalar_t__ bitmap; scalar_t__ sync_thread; scalar_t__ recovery; } ;
struct file {int dummy; } ;
typedef  int ssize_t ;
struct TYPE_4__ {int /*<<< orphan*/  (* quiesce ) (struct mddev*,int) ;} ;

/* Variables and functions */
 int EBUSY ; 
 int EINVAL ; 
 int /*<<< orphan*/  MD_CHANGE_DEVS ; 
 int bitmap_create (struct mddev*) ; 
 int /*<<< orphan*/  bitmap_destroy (struct mddev*) ; 
 int bitmap_load (struct mddev*) ; 
 int /*<<< orphan*/  fput (struct file*) ; 
 int kstrtoll (char const*,int,long long*) ; 
 int /*<<< orphan*/  md_wakeup_thread (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  restore_bitmap_write_access (struct file*) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ strncmp (char const*,char*,int) ; 
 int /*<<< orphan*/  stub1 (struct mddev*,int) ; 
 int /*<<< orphan*/  stub2 (struct mddev*,int) ; 
 int /*<<< orphan*/  stub3 (struct mddev*,int) ; 
 int /*<<< orphan*/  stub4 (struct mddev*,int) ; 

__attribute__((used)) static ssize_t
location_store(struct mddev *mddev, const char *buf, size_t len)
{

	if (mddev->pers) {
		if (!mddev->pers->quiesce)
			return -EBUSY;
		if (mddev->recovery || mddev->sync_thread)
			return -EBUSY;
	}

	if (mddev->bitmap || mddev->bitmap_info.file ||
	    mddev->bitmap_info.offset) {
		/* bitmap already configured.  Only option is to clear it */
		if (strncmp(buf, "none", 4) != 0)
			return -EBUSY;
		if (mddev->pers) {
			mddev->pers->quiesce(mddev, 1);
			bitmap_destroy(mddev);
			mddev->pers->quiesce(mddev, 0);
		}
		mddev->bitmap_info.offset = 0;
		if (mddev->bitmap_info.file) {
			struct file *f = mddev->bitmap_info.file;
			mddev->bitmap_info.file = NULL;
			restore_bitmap_write_access(f);
			fput(f);
		}
	} else {
		/* No bitmap, OK to set a location */
		long long offset;
		if (strncmp(buf, "none", 4) == 0)
			/* nothing to be done */;
		else if (strncmp(buf, "file:", 5) == 0) {
			/* Not supported yet */
			return -EINVAL;
		} else {
			int rv;
			if (buf[0] == '+')
				rv = kstrtoll(buf+1, 10, &offset);
			else
				rv = kstrtoll(buf, 10, &offset);
			if (rv)
				return rv;
			if (offset == 0)
				return -EINVAL;
			if (mddev->bitmap_info.external == 0 &&
			    mddev->major_version == 0 &&
			    offset != mddev->bitmap_info.default_offset)
				return -EINVAL;
			mddev->bitmap_info.offset = offset;
			if (mddev->pers) {
				mddev->pers->quiesce(mddev, 1);
				rv = bitmap_create(mddev);
				if (!rv)
					rv = bitmap_load(mddev);
				if (rv) {
					bitmap_destroy(mddev);
					mddev->bitmap_info.offset = 0;
				}
				mddev->pers->quiesce(mddev, 0);
				if (rv)
					return rv;
			}
		}
	}
	if (!mddev->external) {
		/* Ensure new bitmap info is stored in
		 * metadata promptly.
		 */
		set_bit(MD_CHANGE_DEVS, &mddev->flags);
		md_wakeup_thread(mddev->thread);
	}
	return len;
}