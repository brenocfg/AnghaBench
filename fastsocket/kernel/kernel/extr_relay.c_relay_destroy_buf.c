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
struct rchan_buf {unsigned int page_count; size_t cpu; struct rchan_buf* padding; int /*<<< orphan*/ * page_array; int /*<<< orphan*/  start; struct rchan* chan; } ;
struct rchan {int /*<<< orphan*/  kref; int /*<<< orphan*/ ** buf; } ;

/* Variables and functions */
 int /*<<< orphan*/  __free_page (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct rchan_buf*) ; 
 int /*<<< orphan*/  kref_put (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ likely (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  relay_destroy_channel ; 
 int /*<<< orphan*/  relay_free_page_array (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vunmap (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void relay_destroy_buf(struct rchan_buf *buf)
{
	struct rchan *chan = buf->chan;
	unsigned int i;

	if (likely(buf->start)) {
		vunmap(buf->start);
		for (i = 0; i < buf->page_count; i++)
			__free_page(buf->page_array[i]);
		relay_free_page_array(buf->page_array);
	}
	chan->buf[buf->cpu] = NULL;
	kfree(buf->padding);
	kfree(buf);
	kref_put(&chan->kref, relay_destroy_channel);
}