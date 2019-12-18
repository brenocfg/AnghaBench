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
struct sock {int dummy; } ;
struct sk_buff {int dummy; } ;
struct dn_scp {int numdat_rcv; int numoth_rcv; unsigned short ackxmt_dat; unsigned short ackxmt_oth; } ;
typedef  int /*<<< orphan*/  __le16 ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 struct dn_scp* DN_SK (struct sock*) ; 
 void* cpu_to_le16 (unsigned short) ; 
 scalar_t__ dn_mk_common_header (struct dn_scp*,struct sk_buff*,unsigned char,int) ; 

__attribute__((used)) static __le16 *dn_mk_ack_header(struct sock *sk, struct sk_buff *skb, unsigned char msgflag, int hlen, int other)
{
	struct dn_scp *scp = DN_SK(sk);
	unsigned short acknum = scp->numdat_rcv & 0x0FFF;
	unsigned short ackcrs = scp->numoth_rcv & 0x0FFF;
	__le16 *ptr;

	BUG_ON(hlen < 9);

	scp->ackxmt_dat = acknum;
	scp->ackxmt_oth = ackcrs;
	acknum |= 0x8000;
	ackcrs |= 0x8000;

	/* If this is an "other data/ack" message, swap acknum and ackcrs */
	if (other) {
		unsigned short tmp = acknum;
		acknum = ackcrs;
		ackcrs = tmp;
	}

	/* Set "cross subchannel" bit in ackcrs */
	ackcrs |= 0x2000;

	ptr = (__le16 *)dn_mk_common_header(scp, skb, msgflag, hlen);

	*ptr++ = cpu_to_le16(acknum);
	*ptr++ = cpu_to_le16(ackcrs);

	return ptr;
}