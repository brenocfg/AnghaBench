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
struct sk_buff {int /*<<< orphan*/  csum; int /*<<< orphan*/  len; } ;
typedef  int /*<<< orphan*/  __sum16 ;
typedef  int /*<<< orphan*/  __be32 ;

/* Variables and functions */
 int /*<<< orphan*/  IPPROTO_DCCP ; 
 int /*<<< orphan*/  csum_tcpudp_magic (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline __sum16 dccp_v4_csum_finish(struct sk_buff *skb,
				      __be32 src, __be32 dst)
{
	return csum_tcpudp_magic(src, dst, skb->len, IPPROTO_DCCP, skb->csum);
}