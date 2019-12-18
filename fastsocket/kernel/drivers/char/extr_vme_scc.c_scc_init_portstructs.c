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
struct TYPE_4__ {int /*<<< orphan*/  close_wait; int /*<<< orphan*/  open_wait; int /*<<< orphan*/ * ops; } ;
struct TYPE_3__ {int close_delay; int closing_wait; TYPE_2__ port; int /*<<< orphan*/  port_write_mutex; int /*<<< orphan*/ * rd; int /*<<< orphan*/  magic; } ;
struct scc_port {TYPE_1__ gs; } ;

/* Variables and functions */
 int HZ ; 
 int /*<<< orphan*/  MUTEX ; 
 int /*<<< orphan*/  SCC_MAGIC ; 
 int /*<<< orphan*/  init_waitqueue_head (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  scc_port_ops ; 
 struct scc_port* scc_ports ; 
 int /*<<< orphan*/  scc_real_driver ; 
 int /*<<< orphan*/  tty_port_init (TYPE_2__*) ; 

__attribute__((used)) static void scc_init_portstructs(void)
{
	struct scc_port *port;
	int i;

	for (i = 0; i < 2; i++) {
		port = scc_ports + i;
		tty_port_init(&port->gs.port);
		port->gs.port.ops = &scc_port_ops;
		port->gs.magic = SCC_MAGIC;
		port->gs.close_delay = HZ/2;
		port->gs.closing_wait = 30 * HZ;
		port->gs.rd = &scc_real_driver;
#ifdef NEW_WRITE_LOCKING
		port->gs.port_write_mutex = MUTEX;
#endif
		init_waitqueue_head(&port->gs.port.open_wait);
		init_waitqueue_head(&port->gs.port.close_wait);
	}
}