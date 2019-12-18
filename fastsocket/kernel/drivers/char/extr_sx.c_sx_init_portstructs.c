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
struct TYPE_4__ {int /*<<< orphan*/ * ops; } ;
struct TYPE_3__ {int close_delay; int closing_wait; int /*<<< orphan*/  driver_lock; int /*<<< orphan*/  port_write_mutex; int /*<<< orphan*/ * rd; int /*<<< orphan*/  magic; TYPE_2__ port; } ;
struct sx_port {int ch_base; int /*<<< orphan*/  line; TYPE_1__ gs; struct sx_board* board; } ;
struct sx_board {int nports; int port_base; struct sx_port* ports; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int HZ ; 
 scalar_t__ IS_SX_BOARD (struct sx_board*) ; 
 int /*<<< orphan*/  MUTEX ; 
 int /*<<< orphan*/  SX_DEBUG_INIT ; 
 int /*<<< orphan*/  SX_DEBUG_PROBE ; 
 int /*<<< orphan*/  SX_MAGIC ; 
 struct sx_board* boards ; 
 int /*<<< orphan*/  func_enter () ; 
 int /*<<< orphan*/  func_exit () ; 
 struct sx_port* kcalloc (int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mc_chan_pointer ; 
 int /*<<< orphan*/  mc_type ; 
 int read_sx_word (struct sx_board*,int) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sx_dprintk (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  sx_port_ops ; 
 struct sx_port* sx_ports ; 
 int sx_read_module_byte (struct sx_board*,int,int /*<<< orphan*/ ) ; 
 int sx_read_module_word (struct sx_board*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sx_real_driver ; 
 int /*<<< orphan*/  tty_port_init (TYPE_2__*) ; 

__attribute__((used)) static int sx_init_portstructs(int nboards, int nports)
{
	struct sx_board *board;
	struct sx_port *port;
	int i, j;
	int addr, chans;
	int portno;

	func_enter();

	/* Many drivers statically allocate the maximum number of ports
	   There is no reason not to allocate them dynamically.
	   Is there? -- REW */
	sx_ports = kcalloc(nports, sizeof(struct sx_port), GFP_KERNEL);
	if (!sx_ports)
		return -ENOMEM;

	port = sx_ports;
	for (i = 0; i < nboards; i++) {
		board = &boards[i];
		board->ports = port;
		for (j = 0; j < boards[i].nports; j++) {
			sx_dprintk(SX_DEBUG_INIT, "initing port %d\n", j);
			tty_port_init(&port->gs.port);
			port->gs.port.ops = &sx_port_ops;
			port->gs.magic = SX_MAGIC;
			port->gs.close_delay = HZ / 2;
			port->gs.closing_wait = 30 * HZ;
			port->board = board;
			port->gs.rd = &sx_real_driver;
#ifdef NEW_WRITE_LOCKING
			port->gs.port_write_mutex = MUTEX;
#endif
			spin_lock_init(&port->gs.driver_lock);
			/*
			 * Initializing wait queue
			 */
			port++;
		}
	}

	port = sx_ports;
	portno = 0;
	for (i = 0; i < nboards; i++) {
		board = &boards[i];
		board->port_base = portno;
		/* Possibly the configuration was rejected. */
		sx_dprintk(SX_DEBUG_PROBE, "Board has %d channels\n",
				board->nports);
		if (board->nports <= 0)
			continue;
		/* XXX byteorder ?? */
		for (addr = 0x80; addr != 0;
				addr = read_sx_word(board, addr) & 0x7fff) {
			chans = sx_read_module_byte(board, addr, mc_type);
			sx_dprintk(SX_DEBUG_PROBE, "Module at %x: %d "
					"channels\n", addr, chans);
			sx_dprintk(SX_DEBUG_PROBE, "Port at");
			for (j = 0; j < chans; j++) {
				/* The "sx-way" is the way it SHOULD be done.
				   That way in the future, the firmware may for
				   example pack the structures a bit more
				   efficient. Neil tells me it isn't going to
				   happen anytime soon though. */
				if (IS_SX_BOARD(board))
					port->ch_base = sx_read_module_word(
							board, addr + j * 2,
							mc_chan_pointer);
				else
					port->ch_base = addr + 0x100 + 0x300 *j;

				sx_dprintk(SX_DEBUG_PROBE, " %x",
						port->ch_base);
				port->line = portno++;
				port++;
			}
			sx_dprintk(SX_DEBUG_PROBE, "\n");
		}
		/* This has to be done earlier. */
		/* board->flags |= SX_BOARD_INITIALIZED; */
	}

	func_exit();
	return 0;
}