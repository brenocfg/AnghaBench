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
struct tcp_sock {struct tcp_sack_block* recv_sack_cache; } ;
struct tcp_sack_block {int dummy; } ;

/* Variables and functions */
 int ARRAY_SIZE (struct tcp_sack_block*) ; 

__attribute__((used)) static int tcp_sack_cache_ok(struct tcp_sock *tp, struct tcp_sack_block *cache)
{
	return cache < tp->recv_sack_cache + ARRAY_SIZE(tp->recv_sack_cache);
}