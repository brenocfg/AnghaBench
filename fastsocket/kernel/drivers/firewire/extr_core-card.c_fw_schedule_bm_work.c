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
struct fw_card {int /*<<< orphan*/  work; } ;

/* Variables and functions */
 int /*<<< orphan*/  fw_card_get (struct fw_card*) ; 
 int /*<<< orphan*/  fw_card_put (struct fw_card*) ; 
 int schedule_delayed_work (int /*<<< orphan*/ *,unsigned long) ; 

void fw_schedule_bm_work(struct fw_card *card, unsigned long delay)
{
	int scheduled;

	fw_card_get(card);
	scheduled = schedule_delayed_work(&card->work, delay);
	if (!scheduled)
		fw_card_put(card);
}