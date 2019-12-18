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
struct ipmi_recv_msg {int dummy; } ;

/* Variables and functions */
 scalar_t__ atomic_dec_and_test (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  complete (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  heartbeat_tofree ; 
 int /*<<< orphan*/  heartbeat_wait ; 

__attribute__((used)) static void heartbeat_free_recv(struct ipmi_recv_msg *msg)
{
    if (atomic_dec_and_test(&heartbeat_tofree))
	    complete(&heartbeat_wait);
}