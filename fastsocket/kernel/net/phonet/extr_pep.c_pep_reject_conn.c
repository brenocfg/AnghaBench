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
typedef  scalar_t__ u8 ;
struct sock {int dummy; } ;
struct sk_buff {int dummy; } ;
typedef  int /*<<< orphan*/  data ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_ATOMIC ; 
#define  PAD 128 
 scalar_t__ PN_PIPE_NO_ERROR ; 
 int /*<<< orphan*/  WARN_ON (int) ; 
 int pep_reply (struct sock*,struct sk_buff*,scalar_t__,scalar_t__ const*,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int pep_reject_conn(struct sock *sk, struct sk_buff *skb, u8 code)
{
	static const u8 data[4] = { PAD, PAD, PAD, 0 /* sub-blocks */ };
	WARN_ON(code == PN_PIPE_NO_ERROR);
	return pep_reply(sk, skb, code, data, sizeof(data), GFP_ATOMIC);
}