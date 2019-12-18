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
typedef  int /*<<< orphan*/  u32 ;
struct tcp_md5sig_key {int dummy; } ;
struct sk_buff {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  tcp_v6_send_response (struct sk_buff*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct tcp_md5sig_key*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void tcp_v6_send_ack(struct sk_buff *skb, u32 seq, u32 ack, u32 win, u32 ts,
			    struct tcp_md5sig_key *key)
{
	tcp_v6_send_response(skb, seq, ack, win, ts, key, 0);
}