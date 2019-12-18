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
struct mad_rmpp_recv {int /*<<< orphan*/  ah; int /*<<< orphan*/  comp; } ;

/* Variables and functions */
 int /*<<< orphan*/  deref_rmpp_recv (struct mad_rmpp_recv*) ; 
 int /*<<< orphan*/  ib_destroy_ah (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct mad_rmpp_recv*) ; 
 int /*<<< orphan*/  wait_for_completion (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void destroy_rmpp_recv(struct mad_rmpp_recv *rmpp_recv)
{
	deref_rmpp_recv(rmpp_recv);
	wait_for_completion(&rmpp_recv->comp);
	ib_destroy_ah(rmpp_recv->ah);
	kfree(rmpp_recv);
}