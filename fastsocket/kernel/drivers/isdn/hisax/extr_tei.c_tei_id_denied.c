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
struct sk_buff {unsigned int* data; } ;
struct TYPE_4__ {int /*<<< orphan*/  (* printdebug ) (TYPE_2__*,char*,int,int) ;} ;
struct TYPE_3__ {TYPE_2__ tei_m; scalar_t__ debug; } ;
struct PStack {TYPE_1__ ma; } ;
struct FsmInst {struct PStack* userdata; } ;

/* Variables and functions */
 int /*<<< orphan*/  stub1 (TYPE_2__*,char*,int,int) ; 

__attribute__((used)) static void
tei_id_denied(struct FsmInst *fi, int event, void *arg)
{
	struct PStack *st = fi->userdata;
	struct sk_buff *skb = arg;
	int ri, tei;

	ri = ((unsigned int) skb->data[1] << 8) + skb->data[2];
	tei = skb->data[4] >> 1;
	if (st->ma.debug)
		st->ma.tei_m.printdebug(&st->ma.tei_m,
			"identity denied ri %d tei %d", ri, tei);
}