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
struct TYPE_2__ {int /*<<< orphan*/  tmp; } ;
struct rsxx_cardinfo {TYPE_1__ log; } ;

/* Variables and functions */
 int /*<<< orphan*/  CARD_TO_DEV (struct rsxx_cardinfo*) ; 
 int /*<<< orphan*/  CREG_ADD_LOG ; 
 int /*<<< orphan*/  CREG_OP_READ ; 
 int creg_queue_cmd (struct rsxx_cardinfo*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  read_hw_log_done ; 

int rsxx_read_hw_log(struct rsxx_cardinfo *card)
{
	int st;

	st = creg_queue_cmd(card, CREG_OP_READ, CREG_ADD_LOG,
			    sizeof(card->log.tmp), card->log.tmp,
			    1, read_hw_log_done, NULL);
	if (st)
		dev_err(CARD_TO_DEV(card),
			"Failed getting log text\n");

	return st;
}