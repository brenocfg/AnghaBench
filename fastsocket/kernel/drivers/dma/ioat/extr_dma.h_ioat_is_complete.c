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
struct ioat_chan_common {int /*<<< orphan*/  completed_cookie; } ;
struct dma_chan {int /*<<< orphan*/  cookie; } ;
typedef  enum dma_status { ____Placeholder_dma_status } dma_status ;
typedef  int /*<<< orphan*/  dma_cookie_t ;

/* Variables and functions */
 int dma_async_is_complete (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct ioat_chan_common* to_chan_common (struct dma_chan*) ; 

__attribute__((used)) static inline enum dma_status
ioat_is_complete(struct dma_chan *c, dma_cookie_t cookie,
		 dma_cookie_t *done, dma_cookie_t *used)
{
	struct ioat_chan_common *chan = to_chan_common(c);
	dma_cookie_t last_used;
	dma_cookie_t last_complete;

	last_used = c->cookie;
	last_complete = chan->completed_cookie;

	if (done)
		*done = last_complete;
	if (used)
		*used = last_used;

	return dma_async_is_complete(cookie, last_complete, last_used);
}