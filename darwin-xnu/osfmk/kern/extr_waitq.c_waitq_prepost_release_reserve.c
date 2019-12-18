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
typedef  int /*<<< orphan*/  uint64_t ;
struct wq_prepost {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  wq_prepost_release_rlist (struct wq_prepost*) ; 
 struct wq_prepost* wq_prepost_rfirst (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wqdbg_v (char*,int /*<<< orphan*/ ) ; 

void waitq_prepost_release_reserve(uint64_t id)
{
	struct wq_prepost *wqp;

	wqdbg_v("releasing reserved preposts starting at: 0x%llx", id);

	wqp = wq_prepost_rfirst(id);
	if (!wqp)
		return;

	wq_prepost_release_rlist(wqp);
}