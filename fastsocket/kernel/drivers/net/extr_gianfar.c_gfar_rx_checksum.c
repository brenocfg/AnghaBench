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
struct sk_buff {int /*<<< orphan*/  ip_summed; } ;
struct rxfcb {int flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  CHECKSUM_NONE ; 
 int /*<<< orphan*/  CHECKSUM_UNNECESSARY ; 
 int RXFCB_CIP ; 
 int RXFCB_CSUM_MASK ; 
 int RXFCB_CTU ; 

__attribute__((used)) static inline void gfar_rx_checksum(struct sk_buff *skb, struct rxfcb *fcb)
{
	/* If valid headers were found, and valid sums
	 * were verified, then we tell the kernel that no
	 * checksumming is necessary.  Otherwise, it is */
	if ((fcb->flags & RXFCB_CSUM_MASK) == (RXFCB_CIP | RXFCB_CTU))
		skb->ip_summed = CHECKSUM_UNNECESSARY;
	else
		skb->ip_summed = CHECKSUM_NONE;
}