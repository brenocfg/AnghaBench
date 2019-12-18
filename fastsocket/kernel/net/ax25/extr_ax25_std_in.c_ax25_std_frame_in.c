#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct sk_buff {int dummy; } ;
struct TYPE_9__ {int state; } ;
typedef  TYPE_1__ ax25_cb ;

/* Variables and functions */
#define  AX25_STATE_1 131 
#define  AX25_STATE_2 130 
#define  AX25_STATE_3 129 
#define  AX25_STATE_4 128 
 int ax25_decode (TYPE_1__*,struct sk_buff*,int*,int*,int*) ; 
 int /*<<< orphan*/  ax25_kick (TYPE_1__*) ; 
 int ax25_std_state1_machine (TYPE_1__*,struct sk_buff*,int,int,int) ; 
 int ax25_std_state2_machine (TYPE_1__*,struct sk_buff*,int,int,int) ; 
 int ax25_std_state3_machine (TYPE_1__*,struct sk_buff*,int,int,int,int,int) ; 
 int ax25_std_state4_machine (TYPE_1__*,struct sk_buff*,int,int,int,int,int) ; 

int ax25_std_frame_in(ax25_cb *ax25, struct sk_buff *skb, int type)
{
	int queued = 0, frametype, ns, nr, pf;

	frametype = ax25_decode(ax25, skb, &ns, &nr, &pf);

	switch (ax25->state) {
	case AX25_STATE_1:
		queued = ax25_std_state1_machine(ax25, skb, frametype, pf, type);
		break;
	case AX25_STATE_2:
		queued = ax25_std_state2_machine(ax25, skb, frametype, pf, type);
		break;
	case AX25_STATE_3:
		queued = ax25_std_state3_machine(ax25, skb, frametype, ns, nr, pf, type);
		break;
	case AX25_STATE_4:
		queued = ax25_std_state4_machine(ax25, skb, frametype, ns, nr, pf, type);
		break;
	}

	ax25_kick(ax25);

	return queued;
}