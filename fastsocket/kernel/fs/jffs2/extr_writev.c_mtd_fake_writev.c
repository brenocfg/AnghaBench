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
struct mtd_info {int (* write ) (struct mtd_info*,size_t,size_t,size_t*,int /*<<< orphan*/ ) ;} ;
struct kvec {size_t iov_len; int /*<<< orphan*/  iov_base; } ;
typedef  size_t loff_t ;

/* Variables and functions */
 int stub1 (struct mtd_info*,size_t,size_t,size_t*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline int mtd_fake_writev(struct mtd_info *mtd, const struct kvec *vecs,
				  unsigned long count, loff_t to, size_t *retlen)
{
	unsigned long i;
	size_t totlen = 0, thislen;
	int ret = 0;

	for (i=0; i<count; i++) {
		if (!vecs[i].iov_len)
			continue;
		ret = mtd->write(mtd, to, vecs[i].iov_len, &thislen, vecs[i].iov_base);
		totlen += thislen;
		if (ret || thislen != vecs[i].iov_len)
			break;
		to += vecs[i].iov_len;
	}
	if (retlen)
		*retlen = totlen;
	return ret;
}