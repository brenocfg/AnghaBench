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
typedef  int /*<<< orphan*/  u_int8_t ;
typedef  int /*<<< orphan*/  u_char ;
struct tcpcb {int dummy; } ;
struct tcp_cache_key_src {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  tcp_cache_key_src_create (struct tcpcb*,struct tcp_cache_key_src*) ; 
 int /*<<< orphan*/  tcp_cache_set_cookie_common (struct tcp_cache_key_src*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

void tcp_cache_set_cookie(struct tcpcb *tp, u_char *cookie, u_int8_t len)
{
	struct tcp_cache_key_src tcks;

	tcp_cache_key_src_create(tp, &tcks);
	tcp_cache_set_cookie_common(&tcks, cookie, len);
}