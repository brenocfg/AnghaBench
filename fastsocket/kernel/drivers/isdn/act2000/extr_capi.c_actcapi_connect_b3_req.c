#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct sk_buff {int dummy; } ;
struct TYPE_11__ {int len; int modulo; } ;
struct TYPE_8__ {TYPE_5__ ncpi; int /*<<< orphan*/  plci; } ;
struct TYPE_7__ {TYPE_2__ connect_b3_req; } ;
struct TYPE_9__ {TYPE_1__ msg; } ;
typedef  TYPE_3__ actcapi_msg ;
struct TYPE_10__ {int /*<<< orphan*/  plci; } ;
typedef  TYPE_4__ act2000_chan ;
typedef  int /*<<< orphan*/  act2000_card ;

/* Variables and functions */
 int /*<<< orphan*/  ACTCAPI_CHKSKB ; 
 int /*<<< orphan*/  ACTCAPI_MKHDR (int,int,int) ; 
 int /*<<< orphan*/  ACTCAPI_QUEUE_TX ; 
 int /*<<< orphan*/  memset (TYPE_5__*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void
actcapi_connect_b3_req(act2000_card *card, act2000_chan *chan)
{
	actcapi_msg *m;
	struct sk_buff *skb;

	ACTCAPI_MKHDR(17, 0x82, 0x00);
	ACTCAPI_CHKSKB;
	m->msg.connect_b3_req.plci = chan->plci;
	memset(&m->msg.connect_b3_req.ncpi, 0,
	       sizeof(m->msg.connect_b3_req.ncpi));
	m->msg.connect_b3_req.ncpi.len = 13;
	m->msg.connect_b3_req.ncpi.modulo = 8;
	ACTCAPI_QUEUE_TX;
}