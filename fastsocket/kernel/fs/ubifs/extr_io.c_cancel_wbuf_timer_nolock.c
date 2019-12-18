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
struct ubifs_wbuf {int /*<<< orphan*/  timer; scalar_t__ need_sync; scalar_t__ no_timer; } ;

/* Variables and functions */
 int /*<<< orphan*/  hrtimer_cancel (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void cancel_wbuf_timer_nolock(struct ubifs_wbuf *wbuf)
{
	if (wbuf->no_timer)
		return;
	wbuf->need_sync = 0;
	hrtimer_cancel(&wbuf->timer);
}