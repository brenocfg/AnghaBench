#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_8__ ;
typedef  struct TYPE_13__   TYPE_5__ ;
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_11__ {char* msn; size_t pre_device; int pre_channel; int flags; int hupflags; int slavedelay; int chargeint; int dialtimeout; int dialwait; TYPE_2__* master; TYPE_1__* slave; int /*<<< orphan*/  pppbind; int /*<<< orphan*/  triggercps; int /*<<< orphan*/  dialmax; int /*<<< orphan*/  cbdelay; int /*<<< orphan*/  p_encap; int /*<<< orphan*/  l3_proto; int /*<<< orphan*/  l2_proto; int /*<<< orphan*/  charge; int /*<<< orphan*/  onhtime; int /*<<< orphan*/  exclusive; } ;
typedef  TYPE_3__ isdn_net_local ;
struct TYPE_12__ {char* eaz; char* drvid; int secure; int callback; int cbhup; int dialmode; int chargehup; int ihup; int slavedelay; int chargeint; int dialtimeout; int dialwait; char* slave; char* master; int /*<<< orphan*/  pppbind; int /*<<< orphan*/  triggercps; int /*<<< orphan*/  dialmax; int /*<<< orphan*/  cbdelay; int /*<<< orphan*/  p_encap; int /*<<< orphan*/  l3_proto; int /*<<< orphan*/  l2_proto; int /*<<< orphan*/  charge; int /*<<< orphan*/  onhtime; int /*<<< orphan*/  exclusive; int /*<<< orphan*/  name; } ;
typedef  TYPE_4__ isdn_net_ioctl_cfg ;
struct TYPE_13__ {TYPE_3__* local; } ;
typedef  TYPE_5__ isdn_net_dev ;
struct TYPE_14__ {char** drvid; } ;
struct TYPE_10__ {char* name; } ;
struct TYPE_9__ {char* name; } ;

/* Variables and functions */
 int ENODEV ; 
 int HZ ; 
 int ISDN_CHARGEHUP ; 
 int ISDN_NET_CALLBACK ; 
 int ISDN_NET_CBHUP ; 
 int ISDN_NET_CBOUT ; 
 int ISDN_NET_DIALMODE_MASK ; 
 int ISDN_NET_SECURE ; 
 TYPE_8__* dev ; 
 TYPE_5__* isdn_net_findif (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sprintf (char*,char*,char*,int) ; 
 int /*<<< orphan*/  strcpy (char*,char*) ; 
 int strlen (char*) ; 

int
isdn_net_getcfg(isdn_net_ioctl_cfg * cfg)
{
	isdn_net_dev *p = isdn_net_findif(cfg->name);

	if (p) {
		isdn_net_local *lp = p->local;

		strcpy(cfg->eaz, lp->msn);
		cfg->exclusive = lp->exclusive;
		if (lp->pre_device >= 0) {
			sprintf(cfg->drvid, "%s,%d", dev->drvid[lp->pre_device],
				lp->pre_channel);
		} else
			cfg->drvid[0] = '\0';
		cfg->onhtime = lp->onhtime;
		cfg->charge = lp->charge;
		cfg->l2_proto = lp->l2_proto;
		cfg->l3_proto = lp->l3_proto;
		cfg->p_encap = lp->p_encap;
		cfg->secure = (lp->flags & ISDN_NET_SECURE) ? 1 : 0;
		cfg->callback = 0;
		if (lp->flags & ISDN_NET_CALLBACK)
			cfg->callback = 1;
		if (lp->flags & ISDN_NET_CBOUT)
			cfg->callback = 2;
		cfg->cbhup = (lp->flags & ISDN_NET_CBHUP) ? 1 : 0;
		cfg->dialmode = lp->flags & ISDN_NET_DIALMODE_MASK;
		cfg->chargehup = (lp->hupflags & 4) ? 1 : 0;
		cfg->ihup = (lp->hupflags & 8) ? 1 : 0;
		cfg->cbdelay = lp->cbdelay;
		cfg->dialmax = lp->dialmax;
		cfg->triggercps = lp->triggercps;
		cfg->slavedelay = lp->slavedelay / HZ;
		cfg->chargeint = (lp->hupflags & ISDN_CHARGEHUP) ?
		    (lp->chargeint / HZ) : 0;
		cfg->pppbind = lp->pppbind;
		cfg->dialtimeout = lp->dialtimeout >= 0 ? lp->dialtimeout / HZ : -1;
		cfg->dialwait = lp->dialwait / HZ;
		if (lp->slave) {
			if (strlen(lp->slave->name) > 8)
				strcpy(cfg->slave, "too-long");
			else
				strcpy(cfg->slave, lp->slave->name);
		} else
			cfg->slave[0] = '\0';
		if (lp->master) {
			if (strlen(lp->master->name) > 8)
				strcpy(cfg->master, "too-long");
			strcpy(cfg->master, lp->master->name);
		} else
			cfg->master[0] = '\0';
		return 0;
	}
	return -ENODEV;
}