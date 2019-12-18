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
struct sock {struct ncp_server* sk_user_data; } ;
struct TYPE_2__ {int /*<<< orphan*/  tq; scalar_t__ creq; } ;
struct ncp_server {TYPE_1__ tx; int /*<<< orphan*/  (* write_space ) (struct sock*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  schedule_work (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (struct sock*) ; 

void ncp_tcp_write_space(struct sock *sk)
{
	struct ncp_server *server = sk->sk_user_data;
	
	/* We do not need any locking: we first set tx.creq, and then we do sendmsg,
	   not vice versa... */
	server->write_space(sk);
	if (server->tx.creq)
		schedule_work(&server->tx.tq);
}