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
struct TYPE_6__ {int plci; scalar_t__ rejectcause; } ;
struct TYPE_7__ {TYPE_1__ connect_resp; } ;
struct TYPE_8__ {TYPE_2__ msg; } ;
typedef  TYPE_3__ actcapi_msg ;
struct TYPE_9__ {int plci; int /*<<< orphan*/  fsm_state; } ;
typedef  TYPE_4__ act2000_chan ;
typedef  int /*<<< orphan*/  act2000_card ;
typedef  scalar_t__ __u8 ;

/* Variables and functions */
 int /*<<< orphan*/  ACT2000_STATE_IWAIT ; 
 int /*<<< orphan*/  ACT2000_STATE_NULL ; 
 int /*<<< orphan*/  ACTCAPI_CHKSKB ; 
 int /*<<< orphan*/  ACTCAPI_MKHDR (int,int,int) ; 
 int /*<<< orphan*/  ACTCAPI_QUEUE_TX ; 

void
actcapi_connect_resp(act2000_card *card, act2000_chan *chan, __u8 cause)
{
	actcapi_msg *m;
	struct sk_buff *skb;

	ACTCAPI_MKHDR(3, 0x02, 0x03);
	ACTCAPI_CHKSKB;
	m->msg.connect_resp.plci = chan->plci;
	m->msg.connect_resp.rejectcause = cause;
	if (cause) {
		chan->fsm_state = ACT2000_STATE_NULL;
		chan->plci = 0x8000;
	} else
		chan->fsm_state = ACT2000_STATE_IWAIT;
	ACTCAPI_QUEUE_TX;
}