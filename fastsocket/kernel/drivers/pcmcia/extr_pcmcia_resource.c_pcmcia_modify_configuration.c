#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_20__   TYPE_7__ ;
typedef  struct TYPE_19__   TYPE_6__ ;
typedef  struct TYPE_18__   TYPE_5__ ;
typedef  struct TYPE_17__   TYPE_4__ ;
typedef  struct TYPE_16__   TYPE_3__ ;
typedef  struct TYPE_15__   TYPE_2__ ;
typedef  struct TYPE_14__   TYPE_1__ ;
typedef  struct TYPE_13__   TYPE_10__ ;

/* Type definitions */
struct TYPE_13__ {scalar_t__ Vpp; scalar_t__ io_irq; } ;
struct TYPE_14__ {scalar_t__ AssignedIRQ; } ;
struct pcmcia_socket {int state; TYPE_4__* ops; TYPE_3__* io; int /*<<< orphan*/  dev; TYPE_10__ socket; TYPE_1__ irq; } ;
struct pcmcia_device {TYPE_7__* function_config; struct pcmcia_socket* socket; } ;
struct TYPE_18__ {int member_4; int map; int flags; int /*<<< orphan*/  stop; int /*<<< orphan*/  start; int /*<<< orphan*/  speed; int /*<<< orphan*/  member_3; int /*<<< orphan*/  member_2; int /*<<< orphan*/  member_1; int /*<<< orphan*/  member_0; } ;
typedef  TYPE_5__ pccard_io_map ;
struct TYPE_19__ {int Attributes; scalar_t__ Vpp1; scalar_t__ Vpp2; } ;
typedef  TYPE_6__ modconf_t ;
struct TYPE_20__ {int state; int Attributes; } ;
typedef  TYPE_7__ config_t ;
struct TYPE_17__ {int /*<<< orphan*/  (* set_io_map ) (struct pcmcia_socket*,TYPE_5__*) ;scalar_t__ (* set_socket ) (struct pcmcia_socket*,TYPE_10__*) ;} ;
struct TYPE_16__ {TYPE_2__* res; } ;
struct TYPE_15__ {int /*<<< orphan*/  end; int /*<<< orphan*/  start; } ;

/* Variables and functions */
 int CONFIG_LOCKED ; 
 int CONF_ENABLE_IRQ ; 
 int CONF_IO_CHANGE_WIDTH ; 
 int CONF_IRQ_CHANGE_VALID ; 
 int CONF_VCC_CHANGE_VALID ; 
 int CONF_VPP1_CHANGE_VALID ; 
 int CONF_VPP2_CHANGE_VALID ; 
 int EACCES ; 
 int EINVAL ; 
 int EIO ; 
 int ENODEV ; 
 int IO_DATA_PATH_WIDTH_8 ; 
 int /*<<< orphan*/  KERN_WARNING ; 
 int MAP_ACTIVE ; 
 int MAX_IO_WIN ; 
 int SOCKET_PRESENT ; 
 int /*<<< orphan*/  dev_printk (int /*<<< orphan*/ ,int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  ds_dbg (struct pcmcia_socket*,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  io_speed ; 
 int /*<<< orphan*/  mdelay (int) ; 
 scalar_t__ stub1 (struct pcmcia_socket*,TYPE_10__*) ; 
 scalar_t__ stub2 (struct pcmcia_socket*,TYPE_10__*) ; 
 int /*<<< orphan*/  stub3 (struct pcmcia_socket*,TYPE_5__*) ; 
 int /*<<< orphan*/  stub4 (struct pcmcia_socket*,TYPE_5__*) ; 

int pcmcia_modify_configuration(struct pcmcia_device *p_dev,
				modconf_t *mod)
{
	struct pcmcia_socket *s;
	config_t *c;

	s = p_dev->socket;
	c = p_dev->function_config;

	if (!(s->state & SOCKET_PRESENT))
		return -ENODEV;
	if (!(c->state & CONFIG_LOCKED))
		return -EACCES;

	if (mod->Attributes & CONF_IRQ_CHANGE_VALID) {
		if (mod->Attributes & CONF_ENABLE_IRQ) {
			c->Attributes |= CONF_ENABLE_IRQ;
			s->socket.io_irq = s->irq.AssignedIRQ;
		} else {
			c->Attributes &= ~CONF_ENABLE_IRQ;
			s->socket.io_irq = 0;
		}
		s->ops->set_socket(s, &s->socket);
	}

	if (mod->Attributes & CONF_VCC_CHANGE_VALID) {
		ds_dbg(s, 0, "changing Vcc is not allowed at this time\n");
		return -EINVAL;
	}

	/* We only allow changing Vpp1 and Vpp2 to the same value */
	if ((mod->Attributes & CONF_VPP1_CHANGE_VALID) &&
	    (mod->Attributes & CONF_VPP2_CHANGE_VALID)) {
		if (mod->Vpp1 != mod->Vpp2) {
			ds_dbg(s, 0, "Vpp1 and Vpp2 must be the same\n");
			return -EINVAL;
		}
		s->socket.Vpp = mod->Vpp1;
		if (s->ops->set_socket(s, &s->socket)) {
			dev_printk(KERN_WARNING, &s->dev,
				   "Unable to set VPP\n");
			return -EIO;
		}
	} else if ((mod->Attributes & CONF_VPP1_CHANGE_VALID) ||
		   (mod->Attributes & CONF_VPP2_CHANGE_VALID)) {
		ds_dbg(s, 0, "changing Vcc is not allowed at this time\n");
		return -EINVAL;
	}

	if (mod->Attributes & CONF_IO_CHANGE_WIDTH) {
		pccard_io_map io_off = { 0, 0, 0, 0, 1 };
		pccard_io_map io_on;
		int i;

		io_on.speed = io_speed;
		for (i = 0; i < MAX_IO_WIN; i++) {
			if (!s->io[i].res)
				continue;
			io_off.map = i;
			io_on.map = i;

			io_on.flags = MAP_ACTIVE | IO_DATA_PATH_WIDTH_8;
			io_on.start = s->io[i].res->start;
			io_on.stop = s->io[i].res->end;

			s->ops->set_io_map(s, &io_off);
			mdelay(40);
			s->ops->set_io_map(s, &io_on);
		}
	}

	return 0;
}