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
struct ifnet {int dummy; } ;
typedef  int /*<<< orphan*/  caddr_t ;

/* Variables and functions */
 int /*<<< orphan*/  TAILQ_INSERT_TAIL (int /*<<< orphan*/ *,struct ifnet*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  VERIFY (int) ; 
 int /*<<< orphan*/  dlil_if_lock_assert () ; 
 int /*<<< orphan*/  if_detaching_link ; 
 int /*<<< orphan*/  ifnet_delayed_run ; 
 scalar_t__ ifnet_detaching_cnt ; 
 int /*<<< orphan*/  ifnet_detaching_head ; 
 int /*<<< orphan*/  wakeup (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
ifnet_detaching_enqueue(struct ifnet *ifp)
{
	dlil_if_lock_assert();

	++ifnet_detaching_cnt;
	VERIFY(ifnet_detaching_cnt != 0);
	TAILQ_INSERT_TAIL(&ifnet_detaching_head, ifp, if_detaching_link);
	wakeup((caddr_t)&ifnet_delayed_run);
}