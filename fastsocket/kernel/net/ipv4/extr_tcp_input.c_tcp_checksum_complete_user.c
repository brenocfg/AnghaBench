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

/* Variables and functions */
 scalar_t__ __tcp_checksum_complete_user (struct sock*,struct sk_buff*) ; 
 int /*<<< orphan*/  skb_csum_unnecessary (struct sk_buff*) ; 

__attribute__((used)) static inline int tcp_checksum_complete_user(struct sock *sk,
					     struct sk_buff *skb)
{
	return !skb_csum_unnecessary(skb) &&
	       __tcp_checksum_complete_user(sk, skb);
}