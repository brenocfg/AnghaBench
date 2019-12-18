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
struct TYPE_2__ {int devicename; } ;

/* Variables and functions */
 int /*<<< orphan*/  CMPID ; 
 int ENODEV ; 
 int /*<<< orphan*/  IS_VALID_CARD (int) ; 
 int /*<<< orphan*/  cmReqClass0 ; 
 int /*<<< orphan*/  cmReqStartProc ; 
 int /*<<< orphan*/  cmReqType2 ; 
 int /*<<< orphan*/  pr_debug (char*,int) ; 
 TYPE_1__** sc_adapter ; 
 int sendmessage (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

int startproc(int card) 
{
	int status;

	if(!IS_VALID_CARD(card)) {
		pr_debug("Invalid param: %d is not a valid card id\n", card);
		return -ENODEV;
	}

	/*
	 * send start msg 
	 */
       	status = sendmessage(card, CMPID,cmReqType2,
			  cmReqClass0,
			  cmReqStartProc,
			  0,0,NULL);
	pr_debug("%s: Sent startProc\n", sc_adapter[card]->devicename);
	
	return status;
}