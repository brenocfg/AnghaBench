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
struct rchan_buf {size_t subbufs_produced; size_t subbufs_consumed; size_t offset; size_t bytes_consumed; TYPE_1__* chan; } ;
struct TYPE_2__ {size_t subbuf_size; size_t n_subbufs; } ;

/* Variables and functions */
 int /*<<< orphan*/  relay_file_read_consume (struct rchan_buf*,size_t,int /*<<< orphan*/ ) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static int relay_file_read_avail(struct rchan_buf *buf, size_t read_pos)
{
	size_t subbuf_size = buf->chan->subbuf_size;
	size_t n_subbufs = buf->chan->n_subbufs;
	size_t produced = buf->subbufs_produced;
	size_t consumed = buf->subbufs_consumed;

	relay_file_read_consume(buf, read_pos, 0);

	consumed = buf->subbufs_consumed;

	if (unlikely(buf->offset > subbuf_size)) {
		if (produced == consumed)
			return 0;
		return 1;
	}

	if (unlikely(produced - consumed >= n_subbufs)) {
		consumed = produced - n_subbufs + 1;
		buf->subbufs_consumed = consumed;
		buf->bytes_consumed = 0;
	}

	produced = (produced % n_subbufs) * subbuf_size + buf->offset;
	consumed = (consumed % n_subbufs) * subbuf_size + buf->bytes_consumed;

	if (consumed > produced)
		produced += n_subbufs * subbuf_size;

	if (consumed == produced) {
		if (buf->offset == subbuf_size &&
		    buf->subbufs_produced > buf->subbufs_consumed)
			return 1;
		return 0;
	}

	return 1;
}