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
struct stripe_head {scalar_t__ bm_seq; int /*<<< orphan*/  lru; int /*<<< orphan*/  state; } ;
struct r5conf {scalar_t__ seq_write; TYPE_1__* mddev; scalar_t__ retry_read_aligned; int /*<<< orphan*/  wait_for_stripe; int /*<<< orphan*/  inactive_list; int /*<<< orphan*/  active_stripes; int /*<<< orphan*/  preread_active_stripes; int /*<<< orphan*/  handle_list; int /*<<< orphan*/  plug; int /*<<< orphan*/  bitmap_list; int /*<<< orphan*/  delayed_list; } ;
struct TYPE_2__ {int /*<<< orphan*/  thread; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 scalar_t__ IO_THRESHOLD ; 
 int /*<<< orphan*/  STRIPE_BIT_DELAY ; 
 int /*<<< orphan*/  STRIPE_DELAYED ; 
 int /*<<< orphan*/  STRIPE_EXPANDING ; 
 int /*<<< orphan*/  STRIPE_HANDLE ; 
 int /*<<< orphan*/  STRIPE_PREREAD_ACTIVE ; 
 int /*<<< orphan*/  atomic_dec (int /*<<< orphan*/ *) ; 
 scalar_t__ atomic_dec_return (int /*<<< orphan*/ *) ; 
 scalar_t__ atomic_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  list_empty (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  md_wakeup_thread (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  plugger_set_plug (int /*<<< orphan*/ *) ; 
 int stripe_operations_active (struct stripe_head*) ; 
 scalar_t__ test_and_clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wake_up (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void do_release_stripe(struct r5conf *conf, struct stripe_head *sh)
{
	BUG_ON(!list_empty(&sh->lru));
	BUG_ON(atomic_read(&conf->active_stripes)==0);
	if (test_bit(STRIPE_HANDLE, &sh->state)) {
		if (test_bit(STRIPE_DELAYED, &sh->state) &&
		    !test_bit(STRIPE_PREREAD_ACTIVE, &sh->state)) {
			list_add_tail(&sh->lru, &conf->delayed_list);
			plugger_set_plug(&conf->plug);
		} else if (test_bit(STRIPE_BIT_DELAY, &sh->state) &&
			   sh->bm_seq - conf->seq_write > 0) {
			list_add_tail(&sh->lru, &conf->bitmap_list);
			plugger_set_plug(&conf->plug);
		} else {
			clear_bit(STRIPE_DELAYED, &sh->state);
			clear_bit(STRIPE_BIT_DELAY, &sh->state);
			list_add_tail(&sh->lru, &conf->handle_list);
		}
		md_wakeup_thread(conf->mddev->thread);
	} else {
		BUG_ON(stripe_operations_active(sh));
		if (test_and_clear_bit(STRIPE_PREREAD_ACTIVE, &sh->state))
			if (atomic_dec_return(&conf->preread_active_stripes)
			    < IO_THRESHOLD)
				md_wakeup_thread(conf->mddev->thread);
		atomic_dec(&conf->active_stripes);
		if (!test_bit(STRIPE_EXPANDING, &sh->state)) {
			list_add_tail(&sh->lru, &conf->inactive_list);
			wake_up(&conf->wait_for_stripe);
			if (conf->retry_read_aligned)
				md_wakeup_thread(conf->mddev->thread);
		}
	}
}