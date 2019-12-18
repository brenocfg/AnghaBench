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
struct connection {int /*<<< orphan*/  swork; int /*<<< orphan*/  flags; TYPE_2__* sock; } ;
struct TYPE_4__ {int /*<<< orphan*/  flags; TYPE_1__* sk; } ;
struct TYPE_3__ {int /*<<< orphan*/  sk_write_pending; } ;

/* Variables and functions */
 int /*<<< orphan*/  CF_APP_LIMITED ; 
 int /*<<< orphan*/  CF_WRITE_PENDING ; 
 int /*<<< orphan*/  SOCK_ASYNC_NOSPACE ; 
 int /*<<< orphan*/  SOCK_NOSPACE ; 
 int /*<<< orphan*/  clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  queue_work (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  send_workqueue ; 
 struct connection* sock2con (struct sock*) ; 
 scalar_t__ test_and_clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  test_and_set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void lowcomms_write_space(struct sock *sk)
{
	struct connection *con = sock2con(sk);

	if (!con)
		return;

	clear_bit(SOCK_NOSPACE, &con->sock->flags);

	if (test_and_clear_bit(CF_APP_LIMITED, &con->flags)) {
		con->sock->sk->sk_write_pending--;
		clear_bit(SOCK_ASYNC_NOSPACE, &con->sock->flags);
	}

	if (!test_and_set_bit(CF_WRITE_PENDING, &con->flags))
		queue_work(send_workqueue, &con->swork);
}