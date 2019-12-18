#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  irqreturn_t ;
struct TYPE_5__ {int dsklen; } ;
struct TYPE_4__ {int /*<<< orphan*/  data; scalar_t__ expires; } ;

/* Variables and functions */
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int /*<<< orphan*/  add_timer (TYPE_1__*) ; 
 int block_flag ; 
 TYPE_2__ custom ; 
 scalar_t__ jiffies ; 
 TYPE_1__ post_write_timer ; 
 int /*<<< orphan*/  selected ; 
 int /*<<< orphan*/  wait_fd_block ; 
 int /*<<< orphan*/  wake_up (int /*<<< orphan*/ *) ; 
 int writepending ; 

__attribute__((used)) static irqreturn_t fd_block_done(int irq, void *dummy)
{
	if (block_flag)
		custom.dsklen = 0x4000;

	if (block_flag == 2) { /* writing */
		writepending = 2;
		post_write_timer.expires = jiffies + 1; /* at least 2 ms */
		post_write_timer.data = selected;
		add_timer(&post_write_timer);
	}
	else {                /* reading */
		block_flag = 0;
		wake_up (&wait_fd_block);
	}
	return IRQ_HANDLED;
}