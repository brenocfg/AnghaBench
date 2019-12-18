#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct sock {int dummy; } ;
struct inet_bind_bucket {int dummy; } ;
struct TYPE_4__ {TYPE_1__* icsk_af_ops; } ;
struct TYPE_3__ {int (* bind_conflict ) (struct sock*,struct inet_bind_bucket*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  SOCK_RELAX ; 
 TYPE_2__* inet_csk (struct sock*) ; 
 int /*<<< orphan*/  sock_reset_flag (struct sock*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sock_set_flag (struct sock*,int /*<<< orphan*/ ) ; 
 int stub1 (struct sock*,struct inet_bind_bucket*) ; 

__attribute__((used)) static int inet_csk_bind_conflict_relax(struct sock *sk,
					struct inet_bind_bucket *tb)
{
	int ret;

	sock_set_flag(sk, SOCK_RELAX);
	ret = inet_csk(sk)->icsk_af_ops->bind_conflict(sk, tb);
	sock_reset_flag(sk, SOCK_RELAX);
	return ret;
}