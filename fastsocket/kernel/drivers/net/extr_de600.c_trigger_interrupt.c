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
struct net_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DE600_SLOW_DOWN ; 
 int /*<<< orphan*/  FLIP_IRQ ; 
 int /*<<< orphan*/  de600_put_command (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  select_nic () ; 
 int /*<<< orphan*/  select_prn () ; 

__attribute__((used)) static inline void trigger_interrupt(struct net_device *dev)
{
	de600_put_command(FLIP_IRQ);
	select_prn();
	DE600_SLOW_DOWN;
	select_nic();
	de600_put_command(0);
}