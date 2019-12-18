#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  scalar_t__ u32 ;
struct sk_buff {int /*<<< orphan*/  ip_summed; } ;

/* Variables and functions */
 int /*<<< orphan*/  CHECKSUM_UNNECESSARY ; 
 scalar_t__ RxProtoMask ; 
 scalar_t__ RxProtoTCP ; 
 scalar_t__ RxProtoUDP ; 
 scalar_t__ TCPFail ; 
 scalar_t__ UDPFail ; 
 int /*<<< orphan*/  skb_checksum_none_assert (struct sk_buff*) ; 

__attribute__((used)) static inline void rtl8169_rx_csum(struct sk_buff *skb, u32 opts1)
{
	u32 status = opts1 & RxProtoMask;

	if (((status == RxProtoTCP) && !(opts1 & TCPFail)) ||
	    ((status == RxProtoUDP) && !(opts1 & UDPFail)))
		skb->ip_summed = CHECKSUM_UNNECESSARY;
	else
		skb_checksum_none_assert(skb);
}