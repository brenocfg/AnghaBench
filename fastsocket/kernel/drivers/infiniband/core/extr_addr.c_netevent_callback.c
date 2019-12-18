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
struct notifier_block {int dummy; } ;
struct neighbour {int nud_state; } ;

/* Variables and functions */
 unsigned long NETEVENT_NEIGH_UPDATE ; 
 int NUD_VALID ; 
 int /*<<< orphan*/  jiffies ; 
 int /*<<< orphan*/  set_timeout (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int netevent_callback(struct notifier_block *self, unsigned long event,
	void *ctx)
{
	if (event == NETEVENT_NEIGH_UPDATE) {
		struct neighbour *neigh = ctx;

		if (neigh->nud_state & NUD_VALID) {
			set_timeout(jiffies);
		}
	}
	return 0;
}