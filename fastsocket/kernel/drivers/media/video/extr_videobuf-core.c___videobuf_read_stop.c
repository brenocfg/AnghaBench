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
struct videobuf_queue {int /*<<< orphan*/ * read_buf; int /*<<< orphan*/ ** bufs; int /*<<< orphan*/  stream; } ;

/* Variables and functions */
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int VIDEO_MAX_FRAME ; 
 int /*<<< orphan*/  __videobuf_free (struct videobuf_queue*) ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  videobuf_queue_cancel (struct videobuf_queue*) ; 

__attribute__((used)) static void __videobuf_read_stop(struct videobuf_queue *q)
{
	int i;

	videobuf_queue_cancel(q);
	__videobuf_free(q);
	INIT_LIST_HEAD(&q->stream);
	for (i = 0; i < VIDEO_MAX_FRAME; i++) {
		if (NULL == q->bufs[i])
			continue;
		kfree(q->bufs[i]);
		q->bufs[i] = NULL;
	}
	q->read_buf = NULL;
}