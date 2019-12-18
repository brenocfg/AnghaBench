#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct pcmcia_socket {int dummy; } ;
struct pcmcia_device {scalar_t__ _io; TYPE_3__* function_config; struct pcmcia_socket* socket; } ;
struct TYPE_6__ {scalar_t__ BasePort1; scalar_t__ NumPorts1; scalar_t__ BasePort2; scalar_t__ NumPorts2; } ;
typedef  TYPE_2__ io_req_t ;
struct TYPE_5__ {scalar_t__ BasePort1; scalar_t__ NumPorts1; scalar_t__ BasePort2; scalar_t__ NumPorts2; } ;
struct TYPE_7__ {int /*<<< orphan*/  state; TYPE_1__ io; } ;
typedef  TYPE_3__ config_t ;

/* Variables and functions */
 int /*<<< orphan*/  CONFIG_IO_REQ ; 
 int EINVAL ; 
 int /*<<< orphan*/  release_io_space (struct pcmcia_socket*,scalar_t__,scalar_t__) ; 

__attribute__((used)) static int pcmcia_release_io(struct pcmcia_device *p_dev, io_req_t *req)
{
	struct pcmcia_socket *s = p_dev->socket;
	config_t *c = p_dev->function_config;

	if (!p_dev->_io )
		return -EINVAL;

	p_dev->_io = 0;

	if ((c->io.BasePort1 != req->BasePort1) ||
	    (c->io.NumPorts1 != req->NumPorts1) ||
	    (c->io.BasePort2 != req->BasePort2) ||
	    (c->io.NumPorts2 != req->NumPorts2))
		return -EINVAL;

	c->state &= ~CONFIG_IO_REQ;

	release_io_space(s, req->BasePort1, req->NumPorts1);
	if (req->NumPorts2)
		release_io_space(s, req->BasePort2, req->NumPorts2);

	return 0;
}