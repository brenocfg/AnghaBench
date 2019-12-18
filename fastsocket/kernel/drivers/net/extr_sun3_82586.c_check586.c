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
struct scp_struct {scalar_t__ sysbus; int /*<<< orphan*/  iscp; } ;
struct priv {unsigned long base; char* memtop; struct iscp_struct* iscp; struct scp_struct* scp; } ;
struct net_device {int dummy; } ;
struct iscp_struct {int busy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DELAY (int) ; 
 scalar_t__ SCP_DEFAULT_ADDRESS ; 
 scalar_t__ SYSBUSVAL ; 
 scalar_t__ dvma_btov (unsigned long) ; 
 int /*<<< orphan*/  make24 (struct iscp_struct*) ; 
 int /*<<< orphan*/  memset (char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  sun3_attn586 () ; 
 int /*<<< orphan*/  sun3_reset586 () ; 

__attribute__((used)) static int check586(struct net_device *dev,char *where,unsigned size)
{
	struct priv pb;
	struct priv *p = &pb;
	char *iscp_addr;
	int i;

	p->base = (unsigned long) dvma_btov(0);
	p->memtop = (char *)dvma_btov((unsigned long)where);
	p->scp = (struct scp_struct *)(p->base + SCP_DEFAULT_ADDRESS);
	memset((char *)p->scp,0, sizeof(struct scp_struct));
	for(i=0;i<sizeof(struct scp_struct);i++) /* memory was writeable? */
		if(((char *)p->scp)[i])
			return 0;
	p->scp->sysbus = SYSBUSVAL;				/* 1 = 8Bit-Bus, 0 = 16 Bit */
	if(p->scp->sysbus != SYSBUSVAL)
		return 0;

	iscp_addr = (char *)dvma_btov((unsigned long)where);

	p->iscp = (struct iscp_struct *) iscp_addr;
	memset((char *)p->iscp,0, sizeof(struct iscp_struct));

	p->scp->iscp = make24(p->iscp);
	p->iscp->busy = 1;

	sun3_reset586();
	sun3_attn586();
	DELAY(1);	/* wait a while... */

	if(p->iscp->busy) /* i82586 clears 'busy' after successful init */
		return 0;

	return 1;
}