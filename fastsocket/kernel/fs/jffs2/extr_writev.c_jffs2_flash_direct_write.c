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
typedef  int /*<<< orphan*/  uint32_t ;
typedef  int /*<<< orphan*/  u_char ;
struct kvec {unsigned char* iov_base; size_t iov_len; } ;
struct jffs2_sb_info {TYPE_1__* mtd; } ;
typedef  scalar_t__ loff_t ;
struct TYPE_2__ {int (* write ) (TYPE_1__*,scalar_t__,size_t,size_t*,int /*<<< orphan*/  const*) ;} ;

/* Variables and functions */
 scalar_t__ jffs2_sum_active () ; 
 int jffs2_sum_add_kvec (struct jffs2_sb_info*,struct kvec*,int,int /*<<< orphan*/ ) ; 
 int stub1 (TYPE_1__*,scalar_t__,size_t,size_t*,int /*<<< orphan*/  const*) ; 

int jffs2_flash_direct_write(struct jffs2_sb_info *c, loff_t ofs, size_t len,
			size_t *retlen, const u_char *buf)
{
	int ret;
	ret = c->mtd->write(c->mtd, ofs, len, retlen, buf);

	if (jffs2_sum_active()) {
		struct kvec vecs[1];
		int res;

		vecs[0].iov_base = (unsigned char *) buf;
		vecs[0].iov_len = len;

		res = jffs2_sum_add_kvec(c, vecs, 1, (uint32_t) ofs);
		if (res) {
			return res;
		}
	}
	return ret;
}