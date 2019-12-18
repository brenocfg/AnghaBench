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
struct socket {TYPE_1__* sk; } ;
struct connection {struct socket* sock; } ;
struct TYPE_2__ {int /*<<< orphan*/  sk_allocation; struct connection* sk_user_data; int /*<<< orphan*/  sk_state_change; int /*<<< orphan*/  sk_write_space; int /*<<< orphan*/  sk_data_ready; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_NOFS ; 
 int /*<<< orphan*/  lowcomms_data_ready ; 
 int /*<<< orphan*/  lowcomms_state_change ; 
 int /*<<< orphan*/  lowcomms_write_space ; 

__attribute__((used)) static int add_sock(struct socket *sock, struct connection *con)
{
	con->sock = sock;

	/* Install a data_ready callback */
	con->sock->sk->sk_data_ready = lowcomms_data_ready;
	con->sock->sk->sk_write_space = lowcomms_write_space;
	con->sock->sk->sk_state_change = lowcomms_state_change;
	con->sock->sk->sk_user_data = con;
	con->sock->sk->sk_allocation = GFP_NOFS;
	return 0;
}