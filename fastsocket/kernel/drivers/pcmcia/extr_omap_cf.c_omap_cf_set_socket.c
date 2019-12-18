#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  u16 ;
struct socket_state_t {int Vcc; int flags; int /*<<< orphan*/  csc_mask; int /*<<< orphan*/  io_irq; } ;
struct pcmcia_socket {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  CF_CONTROL ; 
 int /*<<< orphan*/  CF_CONTROL_RESET ; 
 int EINVAL ; 
 int SS_RESET ; 
 int /*<<< orphan*/  driver_name ; 
 int /*<<< orphan*/  omap_readw (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  omap_writew (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_debug (char*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
omap_cf_set_socket(struct pcmcia_socket *sock, struct socket_state_t *s)
{
	u16		control;

	/* REVISIT some non-OSK boards may support power switching */
	switch (s->Vcc) {
	case 0:
	case 33:
		break;
	default:
		return -EINVAL;
	}

	control = omap_readw(CF_CONTROL);
	if (s->flags & SS_RESET)
		omap_writew(CF_CONTROL_RESET, CF_CONTROL);
	else
		omap_writew(0, CF_CONTROL);

	pr_debug("%s: Vcc %d, io_irq %d, flags %04x csc %04x\n",
		driver_name, s->Vcc, s->io_irq, s->flags, s->csc_mask);

	return 0;
}