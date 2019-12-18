#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  devicename; TYPE_1__* channel; } ;
struct TYPE_3__ {int l2_proto; } ;

/* Variables and functions */
 int /*<<< orphan*/  CEPID ; 
 int ENODEV ; 
 int /*<<< orphan*/  IS_VALID_CARD (int) ; 
 int /*<<< orphan*/  ceReqCallGetFrameFormat ; 
 int /*<<< orphan*/  ceReqClass0 ; 
 int /*<<< orphan*/  ceReqTypeCall ; 
 int /*<<< orphan*/  pr_debug (char*,int,...) ; 
 TYPE_2__** sc_adapter ; 
 int sendmessage (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned char,int,unsigned int*) ; 

__attribute__((used)) static int setl2(int card, unsigned long arg)
{
	int status =0;
	int protocol,channel;

	if(!IS_VALID_CARD(card)) {
		pr_debug("Invalid param: %d is not a valid card id\n", card);
		return -ENODEV;
	}
	protocol = arg >> 8;
	channel = arg & 0xff;
	sc_adapter[card]->channel[channel].l2_proto = protocol;

	/*
	 * check that the adapter is also set to the correct protocol
	 */
	pr_debug("%s: Sending GetFrameFormat for channel %d\n",
		sc_adapter[card]->devicename, channel+1);
	status = sendmessage(card, CEPID, ceReqTypeCall,
 				ceReqClass0,
 				ceReqCallGetFrameFormat,
 				(unsigned char)channel+1,
 				1,
 				(unsigned int *) protocol);
	if(status) 
		return status;
	return 0;
}