#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
typedef  char u_char ;
struct TYPE_11__ {int TupleDataMax; int DesiredTuple; int /*<<< orphan*/ * TupleData; scalar_t__ TupleOffset; scalar_t__ Attributes; } ;
typedef  TYPE_2__ tuple_t ;
struct TYPE_10__ {int ns; char* str; int* ofs; } ;
struct TYPE_12__ {TYPE_1__ version_1; } ;
struct smc_cfg_mem {char* buf; TYPE_3__ parse; TYPE_2__ tuple; } ;
struct pcmcia_device {struct net_device* priv; } ;
struct net_device {int dummy; } ;
typedef  TYPE_3__ cisparse_t ;
typedef  int /*<<< orphan*/  cisdata_t ;

/* Variables and functions */
 int CISTPL_VERS_1 ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ cvt_ascii_address (struct net_device*,char*) ; 
 scalar_t__ first_tuple (struct pcmcia_device*,TYPE_2__*,TYPE_3__*) ; 
 int /*<<< orphan*/  kfree (struct smc_cfg_mem*) ; 
 struct smc_cfg_mem* kmalloc (int,int /*<<< orphan*/ ) ; 
 scalar_t__ next_tuple (struct pcmcia_device*,TYPE_2__*,TYPE_3__*) ; 
 scalar_t__ pcmcia_get_first_tuple (struct pcmcia_device*,TYPE_2__*) ; 
 scalar_t__ pcmcia_get_tuple_data (struct pcmcia_device*,TYPE_2__*) ; 

__attribute__((used)) static int mhz_setup(struct pcmcia_device *link)
{
    struct net_device *dev = link->priv;
    struct smc_cfg_mem *cfg_mem;
    tuple_t *tuple;
    cisparse_t *parse;
    u_char *buf, *station_addr;
    int rc;

    cfg_mem = kmalloc(sizeof(struct smc_cfg_mem), GFP_KERNEL);
    if (!cfg_mem)
	return -1;

    tuple = &cfg_mem->tuple;
    parse = &cfg_mem->parse;
    buf = cfg_mem->buf;

    tuple->Attributes = tuple->TupleOffset = 0;
    tuple->TupleData = (cisdata_t *)buf;
    tuple->TupleDataMax = 255;

    /* Read the station address from the CIS.  It is stored as the last
       (fourth) string in the Version 1 Version/ID tuple. */
    tuple->DesiredTuple = CISTPL_VERS_1;
    if (first_tuple(link, tuple, parse) != 0) {
	rc = -1;
	goto free_cfg_mem;
    }
    /* Ugh -- the EM1144 card has two VERS_1 tuples!?! */
    if (next_tuple(link, tuple, parse) != 0)
	first_tuple(link, tuple, parse);
    if (parse->version_1.ns > 3) {
	station_addr = parse->version_1.str + parse->version_1.ofs[3];
	if (cvt_ascii_address(dev, station_addr) == 0) {
		rc = 0;
		goto free_cfg_mem;
	}
    }

    /* Another possibility: for the EM3288, in a special tuple */
    tuple->DesiredTuple = 0x81;
    if (pcmcia_get_first_tuple(link, tuple) != 0) {
	rc = -1;
	goto free_cfg_mem;
    }
    if (pcmcia_get_tuple_data(link, tuple) != 0) {
	rc = -1;
	goto free_cfg_mem;
    }
    buf[12] = '\0';
    if (cvt_ascii_address(dev, buf) == 0) {
	rc = 0;
	goto free_cfg_mem;
   }
    rc = -1;
free_cfg_mem:
   kfree(cfg_mem);
   return rc;
}