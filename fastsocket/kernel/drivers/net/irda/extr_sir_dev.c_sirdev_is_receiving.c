#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {scalar_t__ state; } ;
struct sir_dev {TYPE_1__ rx_buff; int /*<<< orphan*/  enable_rx; } ;

/* Variables and functions */
 scalar_t__ OUTSIDE_FRAME ; 
 int /*<<< orphan*/  atomic_read (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int sirdev_is_receiving(struct sir_dev *dev)
{
	if (!atomic_read(&dev->enable_rx))
		return 0;

	return (dev->rx_buff.state != OUTSIDE_FRAME);
}