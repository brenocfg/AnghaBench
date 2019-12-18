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
struct perf_record {int page_size; int /*<<< orphan*/  samples; } ;
struct perf_mmap {unsigned int prev; unsigned char* base; unsigned int mask; } ;

/* Variables and functions */
 unsigned int perf_mmap__read_head (struct perf_mmap*) ; 
 int /*<<< orphan*/  perf_mmap__write_tail (struct perf_mmap*,unsigned int) ; 
 scalar_t__ write_output (struct perf_record*,void*,unsigned long) ; 

__attribute__((used)) static int perf_record__mmap_read(struct perf_record *rec,
				   struct perf_mmap *md)
{
	unsigned int head = perf_mmap__read_head(md);
	unsigned int old = md->prev;
	unsigned char *data = md->base + rec->page_size;
	unsigned long size;
	void *buf;
	int rc = 0;

	if (old == head)
		return 0;

	rec->samples++;

	size = head - old;

	if ((old & md->mask) + size != (head & md->mask)) {
		buf = &data[old & md->mask];
		size = md->mask + 1 - (old & md->mask);
		old += size;

		if (write_output(rec, buf, size) < 0) {
			rc = -1;
			goto out;
		}
	}

	buf = &data[old & md->mask];
	size = head - old;
	old += size;

	if (write_output(rec, buf, size) < 0) {
		rc = -1;
		goto out;
	}

	md->prev = old;
	perf_mmap__write_tail(md, old);

out:
	return rc;
}