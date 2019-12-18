#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  wait_q; } ;
struct btmrvl_private {TYPE_2__ main_thread; TYPE_1__* adapter; } ;
struct TYPE_3__ {int /*<<< orphan*/  int_count; scalar_t__ wakeup_tries; int /*<<< orphan*/  ps_state; } ;

/* Variables and functions */
 int /*<<< orphan*/  PS_AWAKE ; 
 int /*<<< orphan*/  wake_up_interruptible (int /*<<< orphan*/ *) ; 

void btmrvl_interrupt(struct btmrvl_private *priv)
{
	priv->adapter->ps_state = PS_AWAKE;

	priv->adapter->wakeup_tries = 0;

	priv->adapter->int_count++;

	wake_up_interruptible(&priv->main_thread.wait_q);
}