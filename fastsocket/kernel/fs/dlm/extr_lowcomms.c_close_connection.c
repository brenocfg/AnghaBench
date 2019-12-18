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
struct connection {int /*<<< orphan*/  sock_mutex; scalar_t__ retries; int /*<<< orphan*/ * rx_page; struct connection* othercon; int /*<<< orphan*/ * sock; } ;

/* Variables and functions */
 int /*<<< orphan*/  __free_page (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sock_release (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void close_connection(struct connection *con, bool and_other)
{
	mutex_lock(&con->sock_mutex);

	if (con->sock) {
		sock_release(con->sock);
		con->sock = NULL;
	}
	if (con->othercon && and_other) {
		/* Will only re-enter once. */
		close_connection(con->othercon, false);
	}
	if (con->rx_page) {
		__free_page(con->rx_page);
		con->rx_page = NULL;
	}

	con->retries = 0;
	mutex_unlock(&con->sock_mutex);
}