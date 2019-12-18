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
struct TYPE_2__ {struct lo_read_data* data; } ;
struct splice_desc {TYPE_1__ u; int /*<<< orphan*/  pos; scalar_t__ flags; int /*<<< orphan*/  total_len; scalar_t__ len; } ;
struct loop_device {struct file* lo_backing_file; } ;
struct lo_read_data {int bsize; int /*<<< orphan*/  offset; int /*<<< orphan*/  page; struct loop_device* lo; } ;
struct file {int dummy; } ;
struct bio_vec {int /*<<< orphan*/  bv_len; int /*<<< orphan*/  bv_offset; int /*<<< orphan*/  bv_page; } ;
typedef  int /*<<< orphan*/  ssize_t ;
typedef  int /*<<< orphan*/  loff_t ;

/* Variables and functions */
 int /*<<< orphan*/  lo_direct_splice_actor ; 
 int /*<<< orphan*/  splice_direct_to_actor (struct file*,struct splice_desc*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static ssize_t
do_lo_receive(struct loop_device *lo,
	      struct bio_vec *bvec, int bsize, loff_t pos)
{
	struct lo_read_data cookie;
	struct splice_desc sd;
	struct file *file;
	ssize_t retval;

	cookie.lo = lo;
	cookie.page = bvec->bv_page;
	cookie.offset = bvec->bv_offset;
	cookie.bsize = bsize;

	sd.len = 0;
	sd.total_len = bvec->bv_len;
	sd.flags = 0;
	sd.pos = pos;
	sd.u.data = &cookie;

	file = lo->lo_backing_file;
	retval = splice_direct_to_actor(file, &sd, lo_direct_splice_actor);

	return retval;
}