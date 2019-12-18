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
struct e1000_adapter {int /*<<< orphan*/  flags; int /*<<< orphan*/  mutex; } ;

/* Variables and functions */
 int /*<<< orphan*/  __E1000_RESETTING ; 
 int /*<<< orphan*/  clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  e1000_down (struct e1000_adapter*) ; 
 int /*<<< orphan*/  e1000_up (struct e1000_adapter*) ; 
 int /*<<< orphan*/  msleep (int) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 scalar_t__ test_and_set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void e1000_reinit_safe(struct e1000_adapter *adapter)
{
	while (test_and_set_bit(__E1000_RESETTING, &adapter->flags))
		msleep(1);
	mutex_lock(&adapter->mutex);
	e1000_down(adapter);
	e1000_up(adapter);
	mutex_unlock(&adapter->mutex);
	clear_bit(__E1000_RESETTING, &adapter->flags);
}