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
struct page {int dummy; } ;
struct loop_device {int /*<<< orphan*/  lo_backing_file; } ;
struct bio_vec {int /*<<< orphan*/  bv_page; int /*<<< orphan*/  bv_len; scalar_t__ bv_offset; } ;
typedef  int ssize_t ;
typedef  int /*<<< orphan*/  loff_t ;

/* Variables and functions */
 int __do_lo_send_write (int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cond_resched () ; 
 scalar_t__ kmap (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kunmap (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int do_lo_send_direct_write(struct loop_device *lo,
		struct bio_vec *bvec, loff_t pos, struct page *page)
{
	ssize_t bw = __do_lo_send_write(lo->lo_backing_file,
			kmap(bvec->bv_page) + bvec->bv_offset,
			bvec->bv_len, pos);
	kunmap(bvec->bv_page);
	cond_resched();
	return bw;
}