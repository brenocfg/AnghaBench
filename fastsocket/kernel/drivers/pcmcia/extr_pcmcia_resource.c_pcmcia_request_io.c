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
struct pcmcia_socket {int state; } ;
struct pcmcia_device {int _io; TYPE_2__* function_config; struct pcmcia_socket* socket; } ;
struct TYPE_4__ {int Attributes1; int Attributes2; int /*<<< orphan*/  NumPorts1; int /*<<< orphan*/  BasePort1; int /*<<< orphan*/  IOAddrLines; int /*<<< orphan*/  NumPorts2; int /*<<< orphan*/  BasePort2; } ;
typedef  TYPE_1__ io_req_t ;
struct TYPE_5__ {int state; TYPE_1__ io; } ;
typedef  TYPE_2__ config_t ;

/* Variables and functions */
 int CONFIG_IO_REQ ; 
 int CONFIG_LOCKED ; 
 int EACCES ; 
 int EBUSY ; 
 int EINVAL ; 
 int ENODEV ; 
 int IO_FORCE_ALIAS_ACCESS ; 
 int IO_SHARED ; 
 int SOCKET_PRESENT ; 
 scalar_t__ alloc_io_space (struct pcmcia_socket*,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ds_dbg (struct pcmcia_socket*,int,char*) ; 
 int /*<<< orphan*/  release_io_space (struct pcmcia_socket*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int pcmcia_request_io(struct pcmcia_device *p_dev, io_req_t *req)
{
	struct pcmcia_socket *s = p_dev->socket;
	config_t *c;

	if (!(s->state & SOCKET_PRESENT))
		return -ENODEV;

	if (!req)
		return -EINVAL;
	c = p_dev->function_config;
	if (c->state & CONFIG_LOCKED)
		return -EACCES;
	if (c->state & CONFIG_IO_REQ) {
		ds_dbg(s, 0, "IO already configured\n");
		return -EBUSY;
	}
	if (req->Attributes1 & (IO_SHARED | IO_FORCE_ALIAS_ACCESS)) {
		ds_dbg(s, 0, "bad attribute setting for IO region 1\n");
		return -EINVAL;
	}
	if ((req->NumPorts2 > 0) &&
	    (req->Attributes2 & (IO_SHARED | IO_FORCE_ALIAS_ACCESS))) {
		ds_dbg(s, 0, "bad attribute setting for IO region 2\n");
		return -EINVAL;
	}

	ds_dbg(s, 1, "trying to allocate resource 1\n");
	if (alloc_io_space(s, req->Attributes1, &req->BasePort1,
			   req->NumPorts1, req->IOAddrLines)) {
		ds_dbg(s, 0, "allocation of resource 1 failed\n");
		return -EBUSY;
	}

	if (req->NumPorts2) {
		ds_dbg(s, 1, "trying to allocate resource 2\n");
		if (alloc_io_space(s, req->Attributes2, &req->BasePort2,
				   req->NumPorts2, req->IOAddrLines)) {
			ds_dbg(s, 0, "allocation of resource 2 failed\n");
			release_io_space(s, req->BasePort1, req->NumPorts1);
			return -EBUSY;
		}
	}

	c->io = *req;
	c->state |= CONFIG_IO_REQ;
	p_dev->_io = 1;
	return 0;
}