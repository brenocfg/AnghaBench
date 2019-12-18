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
struct TYPE_2__ {int /*<<< orphan*/  tq; } ;
struct ncp_server {TYPE_1__ rcv; int /*<<< orphan*/  (* data_ready ) (struct sock*,int) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  schedule_work (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (struct sock*,int) ; 

void ncp_tcp_data_ready(struct sock *sk, int len)
{
	struct ncp_server *server = sk->sk_user_data;

	server->data_ready(sk, len);
	schedule_work(&server->rcv.tq);
}