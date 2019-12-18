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
struct ubifs_info {unsigned long long max_sqnum; int /*<<< orphan*/  cnt_lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  EINVAL ; 
 unsigned long long SQNUM_WARN_WATERMARK ; 
 unsigned long long SQNUM_WATERMARK ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ubifs_err (char*,unsigned long long) ; 
 int /*<<< orphan*/  ubifs_ro_mode (struct ubifs_info*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ubifs_warn (char*) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static unsigned long long next_sqnum(struct ubifs_info *c)
{
	unsigned long long sqnum;

	spin_lock(&c->cnt_lock);
	sqnum = ++c->max_sqnum;
	spin_unlock(&c->cnt_lock);

	if (unlikely(sqnum >= SQNUM_WARN_WATERMARK)) {
		if (sqnum >= SQNUM_WATERMARK) {
			ubifs_err("sequence number overflow %llu, end of life",
				  sqnum);
			ubifs_ro_mode(c, -EINVAL);
		}
		ubifs_warn("running out of sequence numbers, end of life soon");
	}

	return sqnum;
}