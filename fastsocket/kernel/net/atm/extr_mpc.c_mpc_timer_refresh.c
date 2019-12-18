#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  function; scalar_t__ expires; scalar_t__ data; } ;

/* Variables and functions */
 int HZ ; 
 int MPC_P2 ; 
 int /*<<< orphan*/  add_timer (TYPE_1__*) ; 
 scalar_t__ jiffies ; 
 int /*<<< orphan*/  mpc_cache_check ; 
 TYPE_1__ mpc_timer ; 

__attribute__((used)) static void mpc_timer_refresh(void)
{
	mpc_timer.expires = jiffies + (MPC_P2 * HZ);
	mpc_timer.data = mpc_timer.expires;
	mpc_timer.function = mpc_cache_check;
	add_timer(&mpc_timer);

	return;
}