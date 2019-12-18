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
struct mspro_block_data {int /*<<< orphan*/  mrq_handler; } ;
struct memstick_request {int dummy; } ;
struct memstick_dev {int /*<<< orphan*/  next_request; struct memstick_request current_mrq; } ;

/* Variables and functions */
 struct mspro_block_data* memstick_get_drvdata (struct memstick_dev*) ; 

__attribute__((used)) static int h_mspro_block_req_init(struct memstick_dev *card,
				  struct memstick_request **mrq)
{
	struct mspro_block_data *msb = memstick_get_drvdata(card);

	*mrq = &card->current_mrq;
	card->next_request = msb->mrq_handler;
	return 0;
}