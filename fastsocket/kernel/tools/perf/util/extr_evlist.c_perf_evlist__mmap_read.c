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
struct TYPE_2__ {size_t size; } ;
union perf_event {TYPE_1__ header; } ;
struct perf_mmap {unsigned int prev; unsigned char* base; int mask; } ;
struct perf_evlist {scalar_t__ overwrite; union perf_event event_copy; struct perf_mmap* mmap; } ;

/* Variables and functions */
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  memcpy (void*,unsigned char*,unsigned int) ; 
 unsigned int min (int,unsigned int) ; 
 int page_size ; 
 unsigned int perf_mmap__read_head (struct perf_mmap*) ; 
 int /*<<< orphan*/  perf_mmap__write_tail (struct perf_mmap*,unsigned int) ; 
 int /*<<< orphan*/  stderr ; 

union perf_event *perf_evlist__mmap_read(struct perf_evlist *evlist, int idx)
{
	struct perf_mmap *md = &evlist->mmap[idx];
	unsigned int head = perf_mmap__read_head(md);
	unsigned int old = md->prev;
	unsigned char *data = md->base + page_size;
	union perf_event *event = NULL;

	if (evlist->overwrite) {
		/*
		 * If we're further behind than half the buffer, there's a chance
		 * the writer will bite our tail and mess up the samples under us.
		 *
		 * If we somehow ended up ahead of the head, we got messed up.
		 *
		 * In either case, truncate and restart at head.
		 */
		int diff = head - old;
		if (diff > md->mask / 2 || diff < 0) {
			fprintf(stderr, "WARNING: failed to keep up with mmap data.\n");

			/*
			 * head points to a known good entry, start there.
			 */
			old = head;
		}
	}

	if (old != head) {
		size_t size;

		event = (union perf_event *)&data[old & md->mask];
		size = event->header.size;

		/*
		 * Event straddles the mmap boundary -- header should always
		 * be inside due to u64 alignment of output.
		 */
		if ((old & md->mask) + size != ((old + size) & md->mask)) {
			unsigned int offset = old;
			unsigned int len = min(sizeof(*event), size), cpy;
			void *dst = &evlist->event_copy;

			do {
				cpy = min(md->mask + 1 - (offset & md->mask), len);
				memcpy(dst, &data[offset & md->mask], cpy);
				offset += cpy;
				dst += cpy;
				len -= cpy;
			} while (len);

			event = &evlist->event_copy;
		}

		old += size;
	}

	md->prev = old;

	if (!evlist->overwrite)
		perf_mmap__write_tail(md, old);

	return event;
}