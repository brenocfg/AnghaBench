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
struct TYPE_2__ {int /*<<< orphan*/  iov_len; int /*<<< orphan*/  iov_base; } ;
struct kiocb {int ki_nr_segs; scalar_t__ ki_cur_seg; int /*<<< orphan*/  ki_left; TYPE_1__* ki_iovec; int /*<<< orphan*/  ki_buf; TYPE_1__ ki_inline_vec; } ;
typedef  int /*<<< orphan*/  ssize_t ;

/* Variables and functions */

__attribute__((used)) static ssize_t aio_setup_single_vector(struct kiocb *kiocb)
{
	kiocb->ki_iovec = &kiocb->ki_inline_vec;
	kiocb->ki_iovec->iov_base = kiocb->ki_buf;
	kiocb->ki_iovec->iov_len = kiocb->ki_left;
	kiocb->ki_nr_segs = 1;
	kiocb->ki_cur_seg = 0;
	return 0;
}