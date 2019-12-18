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
struct TYPE_3__ {int /*<<< orphan*/  flags; } ;
struct TYPE_4__ {TYPE_1__ port; } ;
struct sx_port {TYPE_2__ gs; } ;

/* Variables and functions */
 int /*<<< orphan*/  GS_TX_INTEN ; 
 int /*<<< orphan*/  func_enter2 () ; 
 int /*<<< orphan*/  func_exit () ; 

__attribute__((used)) static void sx_disable_tx_interrupts(void *ptr)
{
	struct sx_port *port = ptr;
	func_enter2();

	port->gs.port.flags &= ~GS_TX_INTEN;

	func_exit();
}