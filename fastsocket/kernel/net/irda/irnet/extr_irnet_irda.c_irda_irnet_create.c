#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {char* rname; int mask; int /*<<< orphan*/  disconnect_work; int /*<<< orphan*/  tx_flow; int /*<<< orphan*/  ckey; int /*<<< orphan*/  max_sdu_size_rx; void* saddr; void* daddr; void* rsaddr; void* rdaddr; scalar_t__ ttp_connect; scalar_t__ ttp_open; int /*<<< orphan*/  magic; } ;
typedef  TYPE_1__ irnet_socket ;

/* Variables and functions */
 int /*<<< orphan*/  DENTER (int /*<<< orphan*/ ,char*,TYPE_1__*) ; 
 void* DEV_ADDR_ANY ; 
 int /*<<< orphan*/  DEXIT (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  FLOW_START ; 
 int /*<<< orphan*/  INIT_WORK (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IRDA_SOCK_TRACE ; 
 int /*<<< orphan*/  IRNET_MAGIC ; 
 int /*<<< orphan*/  S_LAN ; 
 int /*<<< orphan*/  TTP_SAR_UNBOUND ; 
 int /*<<< orphan*/  irlmp_register_client (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int irlmp_service_to_hint (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  irnet_ppp_disconnect ; 

int
irda_irnet_create(irnet_socket *	self)
{
  DENTER(IRDA_SOCK_TRACE, "(self=0x%p)\n", self);

  self->magic = IRNET_MAGIC;	/* Paranoia */

  self->ttp_open = 0;		/* Prevent higher layer from accessing IrTTP */
  self->ttp_connect = 0;	/* Not connecting yet */
  self->rname[0] = '\0';	/* May be set via control channel */
  self->rdaddr = DEV_ADDR_ANY;	/* May be set via control channel */
  self->rsaddr = DEV_ADDR_ANY;	/* May be set via control channel */
  self->daddr = DEV_ADDR_ANY;	/* Until we get connected */
  self->saddr = DEV_ADDR_ANY;	/* Until we get connected */
  self->max_sdu_size_rx = TTP_SAR_UNBOUND;

  /* Register as a client with IrLMP */
  self->ckey = irlmp_register_client(0, NULL, NULL, NULL);
#ifdef DISCOVERY_NOMASK
  self->mask = 0xffff;		/* For W2k compatibility */
#else /* DISCOVERY_NOMASK */
  self->mask = irlmp_service_to_hint(S_LAN);
#endif /* DISCOVERY_NOMASK */
  self->tx_flow = FLOW_START;	/* Flow control from IrTTP */

  INIT_WORK(&self->disconnect_work, irnet_ppp_disconnect);

  DEXIT(IRDA_SOCK_TRACE, "\n");
  return(0);
}