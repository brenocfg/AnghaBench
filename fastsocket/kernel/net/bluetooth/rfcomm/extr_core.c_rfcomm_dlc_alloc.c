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
struct rfcomm_dlc {int /*<<< orphan*/  refcnt; int /*<<< orphan*/  lock; int /*<<< orphan*/  tx_queue; int /*<<< orphan*/  timer; } ;
typedef  int /*<<< orphan*/  gfp_t ;

/* Variables and functions */
 int /*<<< orphan*/  BT_DBG (char*,struct rfcomm_dlc*) ; 
 int /*<<< orphan*/  atomic_set (int /*<<< orphan*/ *,int) ; 
 struct rfcomm_dlc* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rfcomm_dlc_clear_state (struct rfcomm_dlc*) ; 
 int /*<<< orphan*/  rfcomm_dlc_timeout ; 
 int /*<<< orphan*/  setup_timer (int /*<<< orphan*/ *,int /*<<< orphan*/ ,unsigned long) ; 
 int /*<<< orphan*/  skb_queue_head_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 

struct rfcomm_dlc *rfcomm_dlc_alloc(gfp_t prio)
{
	struct rfcomm_dlc *d = kzalloc(sizeof(*d), prio);

	if (!d)
		return NULL;

	setup_timer(&d->timer, rfcomm_dlc_timeout, (unsigned long)d);

	skb_queue_head_init(&d->tx_queue);
	spin_lock_init(&d->lock);
	atomic_set(&d->refcnt, 1);

	rfcomm_dlc_clear_state(d);

	BT_DBG("%p", d);

	return d;
}