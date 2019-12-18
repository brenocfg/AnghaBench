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
typedef  int /*<<< orphan*/  u_char ;
struct TYPE_2__ {int /*<<< orphan*/  corrected; int /*<<< orphan*/  failed; } ;
struct mtd_info {scalar_t__ size; int (* read ) (struct mtd_info*,scalar_t__,size_t,size_t*,int /*<<< orphan*/ *) ;TYPE_1__ ecc_stats; } ;
struct mtd_concat {int num_subdev; struct mtd_info** subdev; } ;
typedef  scalar_t__ loff_t ;

/* Variables and functions */
 struct mtd_concat* CONCAT (struct mtd_info*) ; 
 int EBADMSG ; 
 int EINVAL ; 
 int EUCLEAN ; 
 int stub1 (struct mtd_info*,scalar_t__,size_t,size_t*,int /*<<< orphan*/ *) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static int
concat_read(struct mtd_info *mtd, loff_t from, size_t len,
	    size_t * retlen, u_char * buf)
{
	struct mtd_concat *concat = CONCAT(mtd);
	int ret = 0, err;
	int i;

	*retlen = 0;

	for (i = 0; i < concat->num_subdev; i++) {
		struct mtd_info *subdev = concat->subdev[i];
		size_t size, retsize;

		if (from >= subdev->size) {
			/* Not destined for this subdev */
			size = 0;
			from -= subdev->size;
			continue;
		}
		if (from + len > subdev->size)
			/* First part goes into this subdev */
			size = subdev->size - from;
		else
			/* Entire transaction goes into this subdev */
			size = len;

		err = subdev->read(subdev, from, size, &retsize, buf);

		/* Save information about bitflips! */
		if (unlikely(err)) {
			if (err == -EBADMSG) {
				mtd->ecc_stats.failed++;
				ret = err;
			} else if (err == -EUCLEAN) {
				mtd->ecc_stats.corrected++;
				/* Do not overwrite -EBADMSG !! */
				if (!ret)
					ret = err;
			} else
				return err;
		}

		*retlen += retsize;
		len -= size;
		if (len == 0)
			return ret;

		buf += size;
		from = 0;
	}
	return -EINVAL;
}