#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {void* io_irq; void* csc_irq; } ;
typedef  TYPE_1__ vrc4171_socket_t ;
struct pcmcia_socket {int features; int map_size; unsigned int sock; int /*<<< orphan*/  pci_irq; scalar_t__ irq_mask; } ;

/* Variables and functions */
 int SS_CAP_PAGE_REGS ; 
 int SS_CAP_PCCARD ; 
 void* search_nonuse_irq () ; 
 int /*<<< orphan*/  vrc4171_irq ; 
 TYPE_1__* vrc4171_sockets ; 

__attribute__((used)) static int pccard_init(struct pcmcia_socket *sock)
{
	vrc4171_socket_t *socket;
	unsigned int slot;

	sock->features |= SS_CAP_PCCARD | SS_CAP_PAGE_REGS;
	sock->irq_mask = 0;
	sock->map_size = 0x1000;
	sock->pci_irq = vrc4171_irq;

	slot = sock->sock;
	socket = &vrc4171_sockets[slot];
	socket->csc_irq = search_nonuse_irq();
	socket->io_irq = search_nonuse_irq();

	return 0;
}