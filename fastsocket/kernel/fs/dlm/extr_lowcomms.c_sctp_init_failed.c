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

/* Variables and functions */
 int /*<<< orphan*/  connections_lock ; 
 int /*<<< orphan*/  foreach_conn (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sctp_init_failed_foreach ; 

__attribute__((used)) static void sctp_init_failed(void)
{
	mutex_lock(&connections_lock);

	foreach_conn(sctp_init_failed_foreach);

	mutex_unlock(&connections_lock);
}