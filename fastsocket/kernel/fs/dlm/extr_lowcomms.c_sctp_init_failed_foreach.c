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
struct connection {int /*<<< orphan*/  swork; int /*<<< orphan*/  flags; scalar_t__ sctp_assoc; } ;

/* Variables and functions */
 int /*<<< orphan*/  CF_CONNECT_PENDING ; 
 int /*<<< orphan*/  CF_WRITE_PENDING ; 
 int /*<<< orphan*/  queue_work (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  send_workqueue ; 
 scalar_t__ test_and_clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  test_and_set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void sctp_init_failed_foreach(struct connection *con)
{
	con->sctp_assoc = 0;
	if (test_and_clear_bit(CF_CONNECT_PENDING, &con->flags)) {
		if (!test_and_set_bit(CF_WRITE_PENDING, &con->flags))
			queue_work(send_workqueue, &con->swork);
	}
}