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
struct TYPE_2__ {int /*<<< orphan*/  devicename; } ;

/* Variables and functions */
 int /*<<< orphan*/  CEPID ; 
 int ENODEV ; 
 int /*<<< orphan*/  IS_VALID_CARD (int) ; 
 int /*<<< orphan*/  ceReqClass1 ; 
 int /*<<< orphan*/  ceReqPhyDisconnect ; 
 int /*<<< orphan*/  ceReqTypePhy ; 
 int /*<<< orphan*/  pr_debug (char*,int,...) ; 
 TYPE_1__** sc_adapter ; 
 int sendmessage (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned char,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int hangup(int card, unsigned long channel)
{
	int status;

	if(!IS_VALID_CARD(card)) {
		pr_debug("Invalid param: %d is not a valid card id\n", card);
		return -ENODEV;
	}

	status = sendmessage(card, CEPID, ceReqTypePhy,
						 ceReqClass1,
						 ceReqPhyDisconnect,
						 (unsigned char) channel+1,
						 0,
						 NULL);
	pr_debug("%s: Sent HANGUP message to channel %lu\n",
		sc_adapter[card]->devicename, channel+1);
	return status;
}