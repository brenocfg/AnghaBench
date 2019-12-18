#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct sk_buff {int dummy; } ;
struct TYPE_6__ {int plci; } ;
struct TYPE_7__ {TYPE_1__ disconnect_resp; } ;
struct TYPE_8__ {TYPE_2__ msg; } ;
typedef  TYPE_3__ actcapi_msg ;
struct TYPE_9__ {int plci; } ;
typedef  TYPE_4__ act2000_chan ;
typedef  int /*<<< orphan*/  act2000_card ;

/* Variables and functions */
 int /*<<< orphan*/  ACTCAPI_CHKSKB ; 
 int /*<<< orphan*/  ACTCAPI_MKHDR (int,int,int) ; 
 int /*<<< orphan*/  ACTCAPI_QUEUE_TX ; 

__attribute__((used)) static void
actcapi_disconnect_resp(act2000_card *card, act2000_chan *chan)
{
	actcapi_msg *m;
	struct sk_buff *skb;

	ACTCAPI_MKHDR(2, 0x04, 0x03);
	ACTCAPI_CHKSKB;
	m->msg.disconnect_resp.plci = chan->plci;
	chan->plci = 0x8000;
	ACTCAPI_QUEUE_TX;
}