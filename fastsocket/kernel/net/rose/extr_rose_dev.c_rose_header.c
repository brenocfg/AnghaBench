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
struct net_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  AX25_P_IP ; 
 int /*<<< orphan*/  ROSE_DATA ; 
 int ROSE_GFI ; 
 scalar_t__ ROSE_MIN_LEN ; 
 int ROSE_Q_BIT ; 
 unsigned char* skb_push (struct sk_buff*,scalar_t__) ; 

__attribute__((used)) static int rose_header(struct sk_buff *skb, struct net_device *dev,
		       unsigned short type,
		       const void *daddr, const void *saddr, unsigned len)
{
	unsigned char *buff = skb_push(skb, ROSE_MIN_LEN + 2);

	*buff++ = ROSE_GFI | ROSE_Q_BIT;
	*buff++ = 0x00;
	*buff++ = ROSE_DATA;
	*buff++ = 0x7F;
	*buff++ = AX25_P_IP;

	if (daddr != NULL)
		return 37;

	return -37;
}