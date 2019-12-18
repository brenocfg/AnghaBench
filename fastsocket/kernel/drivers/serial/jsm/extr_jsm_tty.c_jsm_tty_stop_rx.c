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
struct uart_port {int dummy; } ;
struct jsm_channel {TYPE_2__* ch_bd; } ;
struct TYPE_4__ {TYPE_1__* bd_ops; } ;
struct TYPE_3__ {int /*<<< orphan*/  (* disable_receiver ) (struct jsm_channel*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  stub1 (struct jsm_channel*) ; 

__attribute__((used)) static void jsm_tty_stop_rx(struct uart_port *port)
{
	struct jsm_channel *channel = (struct jsm_channel *)port;

	channel->ch_bd->bd_ops->disable_receiver(channel);
}