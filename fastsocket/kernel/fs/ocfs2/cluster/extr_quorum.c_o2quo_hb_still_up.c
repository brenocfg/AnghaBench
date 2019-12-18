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
typedef  int /*<<< orphan*/  u8 ;
struct o2quo_state {int qs_pending; int /*<<< orphan*/  qs_lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  mlog (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  o2quo_clear_hold (struct o2quo_state*,int /*<<< orphan*/ ) ; 
 struct o2quo_state o2quo_state ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

void o2quo_hb_still_up(u8 node)
{
	struct o2quo_state *qs = &o2quo_state;

	spin_lock(&qs->qs_lock);

	mlog(0, "node %u\n", node);

	qs->qs_pending = 1;
	o2quo_clear_hold(qs, node);

	spin_unlock(&qs->qs_lock);
}