#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u32 ;
struct aoetgt {int /*<<< orphan*/  addr; TYPE_1__* ifp; } ;
struct aoedev {int /*<<< orphan*/  aoeminor; int /*<<< orphan*/  aoemajor; } ;
struct aoe_hdr {int /*<<< orphan*/  tag; int /*<<< orphan*/  cmd; int /*<<< orphan*/  minor; int /*<<< orphan*/  major; int /*<<< orphan*/  verfl; int /*<<< orphan*/  type; int /*<<< orphan*/  dst; int /*<<< orphan*/  src; } ;
struct TYPE_4__ {int /*<<< orphan*/  dev_addr; } ;
struct TYPE_3__ {TYPE_2__* nd; } ;

/* Variables and functions */
 int /*<<< orphan*/  AOECMD_ATA ; 
 int /*<<< orphan*/  AOE_HVER ; 
 int /*<<< orphan*/  ETH_P_AOE ; 
 int /*<<< orphan*/  __constant_cpu_to_be16 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cpu_to_be16 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cpu_to_be32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  newtag (struct aoedev*) ; 

__attribute__((used)) static u32
aoehdr_atainit(struct aoedev *d, struct aoetgt *t, struct aoe_hdr *h)
{
	u32 host_tag = newtag(d);

	memcpy(h->src, t->ifp->nd->dev_addr, sizeof h->src);
	memcpy(h->dst, t->addr, sizeof h->dst);
	h->type = __constant_cpu_to_be16(ETH_P_AOE);
	h->verfl = AOE_HVER;
	h->major = cpu_to_be16(d->aoemajor);
	h->minor = d->aoeminor;
	h->cmd = AOECMD_ATA;
	h->tag = cpu_to_be32(host_tag);

	return host_tag;
}