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
struct TYPE_3__ {int /*<<< orphan*/ * tty; } ;
struct TYPE_4__ {TYPE_1__ port; } ;
struct Port {TYPE_2__ gs; } ;

/* Variables and functions */
 int /*<<< orphan*/  func_enter () ; 
 int /*<<< orphan*/  func_exit () ; 

__attribute__((used)) static void rio_shutdown_port(void *ptr)
{
	struct Port *PortP;

	func_enter();

	PortP = (struct Port *) ptr;
	PortP->gs.port.tty = NULL;
	func_exit();
}