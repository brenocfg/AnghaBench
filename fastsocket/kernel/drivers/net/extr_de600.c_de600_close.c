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
 int /*<<< orphan*/  DE600_IRQ ; 
 int /*<<< orphan*/  RESET ; 
 int /*<<< orphan*/  STOP_RESET ; 
 int /*<<< orphan*/  de600_put_command (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free_irq (int /*<<< orphan*/ ,struct net_device*) ; 
 scalar_t__ rx_page ; 
 int /*<<< orphan*/  select_nic () ; 
 int /*<<< orphan*/  select_prn () ; 

__attribute__((used)) static int de600_close(struct net_device *dev)
{
	select_nic();
	rx_page = 0;
	de600_put_command(RESET);
	de600_put_command(STOP_RESET);
	de600_put_command(0);
	select_prn();
	free_irq(DE600_IRQ, dev);
	return 0;
}