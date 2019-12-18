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
struct st5481_in {TYPE_1__** urb; struct st5481_adapter* adapter; } ;
struct st5481_adapter {int /*<<< orphan*/  usb_dev; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  DBG (int,char*) ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  SUBMIT_URB (TYPE_1__*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void st5481_start_rcv(void *context)
{
	struct st5481_in *in = context;
	struct st5481_adapter *adapter = in->adapter;

	DBG(4,"");

	in->urb[0]->dev = adapter->usb_dev;
	SUBMIT_URB(in->urb[0], GFP_KERNEL);

	in->urb[1]->dev = adapter->usb_dev;
	SUBMIT_URB(in->urb[1], GFP_KERNEL);
}