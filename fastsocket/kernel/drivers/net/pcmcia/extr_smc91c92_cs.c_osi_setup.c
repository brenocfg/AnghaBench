#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u_short ;
typedef  int u_char ;
struct TYPE_7__ {int TupleDataMax; int DesiredTuple; scalar_t__ TupleOffset; int /*<<< orphan*/ * TupleData; int /*<<< orphan*/  Attributes; } ;
typedef  TYPE_2__ tuple_t ;
struct smc_cfg_mem {int* buf; TYPE_2__ tuple; } ;
struct TYPE_6__ {scalar_t__ BasePort1; } ;
struct pcmcia_device {TYPE_1__ io; struct net_device* priv; } ;
struct net_device {int* dev_addr; } ;
typedef  int /*<<< orphan*/  cisdata_t ;

/* Variables and functions */
 int /*<<< orphan*/  DEBUG (int,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ MANFID_OSITECH ; 
 scalar_t__ MANFID_PSION ; 
 scalar_t__ OSITECH_AUI_PWR ; 
 scalar_t__ OSITECH_RESET_ISR ; 
 scalar_t__ PRODID_OSITECH_SEVEN ; 
 scalar_t__ PRODID_PSION_NET100 ; 
 int /*<<< orphan*/  TUPLE_RETURN_COMMON ; 
 int /*<<< orphan*/  inw (scalar_t__) ; 
 int /*<<< orphan*/  kfree (struct smc_cfg_mem*) ; 
 struct smc_cfg_mem* kmalloc (int,int /*<<< orphan*/ ) ; 
 int osi_load_firmware (struct pcmcia_device*) ; 
 int pcmcia_get_first_tuple (struct pcmcia_device*,TYPE_2__*) ; 
 int pcmcia_get_next_tuple (struct pcmcia_device*,TYPE_2__*) ; 
 int pcmcia_get_tuple_data (struct pcmcia_device*,TYPE_2__*) ; 
 int /*<<< orphan*/  set_bits (int,scalar_t__) ; 

__attribute__((used)) static int osi_setup(struct pcmcia_device *link, u_short manfid, u_short cardid)
{
    struct net_device *dev = link->priv;
    struct smc_cfg_mem *cfg_mem;
    tuple_t *tuple;
    u_char *buf;
    int i, rc;

    cfg_mem = kmalloc(sizeof(struct smc_cfg_mem), GFP_KERNEL);
    if (!cfg_mem)
        return -1;

    tuple = &cfg_mem->tuple;
    buf = cfg_mem->buf;

    tuple->Attributes = TUPLE_RETURN_COMMON;
    tuple->TupleData = (cisdata_t *)buf;
    tuple->TupleDataMax = 255;
    tuple->TupleOffset = 0;

    /* Read the station address from tuple 0x90, subtuple 0x04 */
    tuple->DesiredTuple = 0x90;
    i = pcmcia_get_first_tuple(link, tuple);
    while (i == 0) {
	i = pcmcia_get_tuple_data(link, tuple);
	if ((i != 0) || (buf[0] == 0x04))
	    break;
	i = pcmcia_get_next_tuple(link, tuple);
    }
    if (i != 0) {
	rc = -1;
	goto free_cfg_mem;
    }
    for (i = 0; i < 6; i++)
	dev->dev_addr[i] = buf[i+2];

    if (((manfid == MANFID_OSITECH) &&
	 (cardid == PRODID_OSITECH_SEVEN)) ||
	((manfid == MANFID_PSION) &&
	 (cardid == PRODID_PSION_NET100))) {
	rc = osi_load_firmware(link);
	if (rc)
		goto free_cfg_mem;
    } else if (manfid == MANFID_OSITECH) {
	/* Make sure both functions are powered up */
	set_bits(0x300, link->io.BasePort1 + OSITECH_AUI_PWR);
	/* Now, turn on the interrupt for both card functions */
	set_bits(0x300, link->io.BasePort1 + OSITECH_RESET_ISR);
	DEBUG(2, "AUI/PWR: %4.4x RESET/ISR: %4.4x\n",
	      inw(link->io.BasePort1 + OSITECH_AUI_PWR),
	      inw(link->io.BasePort1 + OSITECH_RESET_ISR));
    }
    rc = 0;
free_cfg_mem:
   kfree(cfg_mem);
   return rc;
}