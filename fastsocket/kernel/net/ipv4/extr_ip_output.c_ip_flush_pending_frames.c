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
struct sock {int /*<<< orphan*/  sk_write_queue; } ;
struct inet_cork {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  cork; } ;

/* Variables and functions */
 int /*<<< orphan*/  __ip_flush_pending_frames (struct sock*,int /*<<< orphan*/ *,struct inet_cork*) ; 
 TYPE_1__* inet_sk (struct sock*) ; 

void ip_flush_pending_frames(struct sock *sk)
{
	__ip_flush_pending_frames(sk, &sk->sk_write_queue,
				  (struct inet_cork *)&inet_sk(sk)->cork);
}