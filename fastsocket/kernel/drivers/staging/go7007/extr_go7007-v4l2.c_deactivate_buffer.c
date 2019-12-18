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
struct go7007_buffer {scalar_t__ state; int page_count; int /*<<< orphan*/ * pages; int /*<<< orphan*/  stream; } ;

/* Variables and functions */
 scalar_t__ BUF_STATE_IDLE ; 
 int /*<<< orphan*/  list_del (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  page_cache_release (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void deactivate_buffer(struct go7007_buffer *gobuf)
{
	int i;

	if (gobuf->state != BUF_STATE_IDLE) {
		list_del(&gobuf->stream);
		gobuf->state = BUF_STATE_IDLE;
	}
	if (gobuf->page_count > 0) {
		for (i = 0; i < gobuf->page_count; ++i)
			page_cache_release(gobuf->pages[i]);
		gobuf->page_count = 0;
	}
}