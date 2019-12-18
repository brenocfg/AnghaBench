#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct sk_buff {int dummy; } ;
struct TYPE_8__ {scalar_t__ modulus; int vr; TYPE_2__* ax25_dev; } ;
typedef  TYPE_3__ ax25_cb ;
struct TYPE_7__ {TYPE_1__* dev; } ;
struct TYPE_6__ {int /*<<< orphan*/  hard_header_len; } ;

/* Variables and functions */
 unsigned char AX25_EPF ; 
 scalar_t__ AX25_MODULUS ; 
 unsigned char AX25_PF ; 
 int AX25_S ; 
 int AX25_U ; 
 int /*<<< orphan*/  GFP_ATOMIC ; 
 struct sk_buff* alloc_skb (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ax25_transmit_buffer (TYPE_3__*,struct sk_buff*,int) ; 
 unsigned char* skb_put (struct sk_buff*,int) ; 
 int /*<<< orphan*/  skb_reserve (struct sk_buff*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  skb_reset_network_header (struct sk_buff*) ; 

void ax25_send_control(ax25_cb *ax25, int frametype, int poll_bit, int type)
{
	struct sk_buff *skb;
	unsigned char  *dptr;

	if ((skb = alloc_skb(ax25->ax25_dev->dev->hard_header_len + 2, GFP_ATOMIC)) == NULL)
		return;

	skb_reserve(skb, ax25->ax25_dev->dev->hard_header_len);

	skb_reset_network_header(skb);

	/* Assume a response - address structure for DTE */
	if (ax25->modulus == AX25_MODULUS) {
		dptr = skb_put(skb, 1);
		*dptr = frametype;
		*dptr |= (poll_bit) ? AX25_PF : 0;
		if ((frametype & AX25_U) == AX25_S)		/* S frames carry NR */
			*dptr |= (ax25->vr << 5);
	} else {
		if ((frametype & AX25_U) == AX25_U) {
			dptr = skb_put(skb, 1);
			*dptr = frametype;
			*dptr |= (poll_bit) ? AX25_PF : 0;
		} else {
			dptr = skb_put(skb, 2);
			dptr[0] = frametype;
			dptr[1] = (ax25->vr << 1);
			dptr[1] |= (poll_bit) ? AX25_EPF : 0;
		}
	}

	ax25_transmit_buffer(ax25, skb, type);
}