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
struct TYPE_4__ {int ep; int /*<<< orphan*/ * hisax_if; int /*<<< orphan*/  adapter; int /*<<< orphan*/  counter; int /*<<< orphan*/  packet_size; int /*<<< orphan*/  num_packets; int /*<<< orphan*/  bufsize; } ;
struct TYPE_3__ {int /*<<< orphan*/  ifc; } ;
struct st5481_bcs {TYPE_2__ b_in; TYPE_1__ b_if; int /*<<< orphan*/  adapter; scalar_t__ channel; } ;

/* Variables and functions */
 int /*<<< orphan*/  DBG (int,char*) ; 
 int EP_B1_IN ; 
 int EP_B2_IN ; 
 int /*<<< orphan*/  HSCX_BUFMAX ; 
 int /*<<< orphan*/  IN_B1_COUNTER ; 
 int /*<<< orphan*/  IN_B2_COUNTER ; 
 int /*<<< orphan*/  NUM_ISO_PACKETS_B ; 
 int /*<<< orphan*/  SIZE_ISO_PACKETS_B_IN ; 
 int USB_DIR_IN ; 
 int /*<<< orphan*/  st5481_release_b_out (struct st5481_bcs*) ; 
 int st5481_setup_b_out (struct st5481_bcs*) ; 
 int st5481_setup_in (TYPE_2__*) ; 

int st5481_setup_b(struct st5481_bcs *bcs)
{
	int retval;

	DBG(4,"");

	retval = st5481_setup_b_out(bcs);
	if (retval)
		goto err;
	bcs->b_in.bufsize = HSCX_BUFMAX;
	bcs->b_in.num_packets = NUM_ISO_PACKETS_B;
	bcs->b_in.packet_size = SIZE_ISO_PACKETS_B_IN;
	bcs->b_in.ep = (bcs->channel ? EP_B2_IN : EP_B1_IN) | USB_DIR_IN;
	bcs->b_in.counter = bcs->channel ? IN_B2_COUNTER : IN_B1_COUNTER;
	bcs->b_in.adapter = bcs->adapter;
	bcs->b_in.hisax_if = &bcs->b_if.ifc;
	retval = st5481_setup_in(&bcs->b_in);
	if (retval)
		goto err_b_out;


	return 0;

 err_b_out:
	st5481_release_b_out(bcs);
 err:
	return retval;
}