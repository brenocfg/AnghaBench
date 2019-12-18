#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  counter; } ;
struct sock {TYPE_1__ sk_refcnt; } ;
struct TYPE_5__ {int /*<<< orphan*/  num; } ;

/* Variables and functions */
 TYPE_2__* inet_sk (struct sock*) ; 
 int /*<<< orphan*/  pr_debug (char*,TYPE_2__*,...) ; 
 int /*<<< orphan*/  sk_common_release (struct sock*) ; 

__attribute__((used)) static void ping_close(struct sock *sk, long timeout)
{
	pr_debug("ping_close(sk=%p,sk->num=%u)\n",
		inet_sk(sk), inet_sk(sk)->num);
	pr_debug("isk->refcnt = %d\n", sk->sk_refcnt.counter);

	sk_common_release(sk);
}