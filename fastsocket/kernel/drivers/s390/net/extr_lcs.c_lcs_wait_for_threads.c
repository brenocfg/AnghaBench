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
struct lcs_card {int /*<<< orphan*/  wait_q; } ;

/* Variables and functions */
 scalar_t__ lcs_threads_running (struct lcs_card*,unsigned long) ; 
 int wait_event_interruptible (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int
lcs_wait_for_threads(struct lcs_card *card, unsigned long threads)
{
        return wait_event_interruptible(card->wait_q,
                        lcs_threads_running(card, threads) == 0);
}