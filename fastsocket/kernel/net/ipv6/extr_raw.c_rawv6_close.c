#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct sock {int dummy; } ;
struct TYPE_2__ {scalar_t__ num; } ;

/* Variables and functions */
 scalar_t__ IPPROTO_RAW ; 
 TYPE_1__* inet_sk (struct sock*) ; 
 int /*<<< orphan*/  ip6_ra_control (struct sock*,int) ; 
 int /*<<< orphan*/  ip6mr_sk_done (struct sock*) ; 
 int /*<<< orphan*/  sk_common_release (struct sock*) ; 

__attribute__((used)) static void rawv6_close(struct sock *sk, long timeout)
{
	if (inet_sk(sk)->num == IPPROTO_RAW)
		ip6_ra_control(sk, -1);
	ip6mr_sk_done(sk);
	sk_common_release(sk);
}