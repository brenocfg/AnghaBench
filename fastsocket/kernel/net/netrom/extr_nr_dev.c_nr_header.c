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
struct sk_buff {int dummy; } ;
struct net_device {void const* dev_addr; int /*<<< orphan*/  addr_len; } ;

/* Variables and functions */
 int /*<<< orphan*/  AX25_ADDR_LEN ; 
 unsigned char AX25_CBIT ; 
 unsigned char AX25_EBIT ; 
 unsigned char AX25_SSSID_SPARE ; 
 scalar_t__ NR_NETWORK_LEN ; 
 int /*<<< orphan*/  NR_PROTOEXT ; 
 void* NR_PROTO_IP ; 
 scalar_t__ NR_TRANSPORT_LEN ; 
 int /*<<< orphan*/  memcpy (unsigned char*,void const*,int /*<<< orphan*/ ) ; 
 unsigned char* skb_push (struct sk_buff*,scalar_t__) ; 
 int /*<<< orphan*/  sysctl_netrom_network_ttl_initialiser ; 

__attribute__((used)) static int nr_header(struct sk_buff *skb, struct net_device *dev,
		     unsigned short type,
		     const void *daddr, const void *saddr, unsigned len)
{
	unsigned char *buff = skb_push(skb, NR_NETWORK_LEN + NR_TRANSPORT_LEN);

	memcpy(buff, (saddr != NULL) ? saddr : dev->dev_addr, dev->addr_len);
	buff[6] &= ~AX25_CBIT;
	buff[6] &= ~AX25_EBIT;
	buff[6] |= AX25_SSSID_SPARE;
	buff    += AX25_ADDR_LEN;

	if (daddr != NULL)
		memcpy(buff, daddr, dev->addr_len);
	buff[6] &= ~AX25_CBIT;
	buff[6] |= AX25_EBIT;
	buff[6] |= AX25_SSSID_SPARE;
	buff    += AX25_ADDR_LEN;

	*buff++ = sysctl_netrom_network_ttl_initialiser;

	*buff++ = NR_PROTO_IP;
	*buff++ = NR_PROTO_IP;
	*buff++ = 0;
	*buff++ = 0;
	*buff++ = NR_PROTOEXT;

	if (daddr != NULL)
		return 37;

	return -37;
}