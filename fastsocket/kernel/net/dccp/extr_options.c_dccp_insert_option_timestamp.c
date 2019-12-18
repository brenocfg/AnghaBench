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
typedef  int /*<<< orphan*/  now ;
typedef  int /*<<< orphan*/  __be32 ;

/* Variables and functions */
 int /*<<< orphan*/  DCCPO_TIMESTAMP ; 
 int dccp_insert_option (struct sock*,struct sk_buff*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  dccp_timestamp () ; 
 int /*<<< orphan*/  htonl (int /*<<< orphan*/ ) ; 

int dccp_insert_option_timestamp(struct sock *sk, struct sk_buff *skb)
{
	__be32 now = htonl(dccp_timestamp());
	/* yes this will overflow but that is the point as we want a
	 * 10 usec 32 bit timer which mean it wraps every 11.9 hours */

	return dccp_insert_option(sk, skb, DCCPO_TIMESTAMP, &now, sizeof(now));
}