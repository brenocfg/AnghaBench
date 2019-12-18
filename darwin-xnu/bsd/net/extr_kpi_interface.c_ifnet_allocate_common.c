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
struct ifnet_init_params {int /*<<< orphan*/  broadcast_len; int /*<<< orphan*/  broadcast_addr; int /*<<< orphan*/  event; int /*<<< orphan*/  detach; int /*<<< orphan*/  set_bpf_tap; int /*<<< orphan*/  ioctl; int /*<<< orphan*/  softc; int /*<<< orphan*/  framer; int /*<<< orphan*/  check_multi; int /*<<< orphan*/  del_proto; int /*<<< orphan*/  add_proto; int /*<<< orphan*/  demux; int /*<<< orphan*/  output; int /*<<< orphan*/  type; int /*<<< orphan*/  family; int /*<<< orphan*/  unit; int /*<<< orphan*/  name; int /*<<< orphan*/  uniqueid_len; int /*<<< orphan*/  uniqueid; } ;
struct ifnet_init_eparams {int len; int flags; int /*<<< orphan*/  broadcast_len; int /*<<< orphan*/  broadcast_addr; int /*<<< orphan*/  event; int /*<<< orphan*/  detach; int /*<<< orphan*/  set_bpf_tap; int /*<<< orphan*/  ioctl; int /*<<< orphan*/  softc; int /*<<< orphan*/  framer; int /*<<< orphan*/  check_multi; int /*<<< orphan*/  del_proto; int /*<<< orphan*/  add_proto; int /*<<< orphan*/  demux; int /*<<< orphan*/  output; int /*<<< orphan*/  type; int /*<<< orphan*/  family; int /*<<< orphan*/  unit; int /*<<< orphan*/  name; int /*<<< orphan*/  uniqueid_len; int /*<<< orphan*/  uniqueid; int /*<<< orphan*/  ver; } ;
typedef  int /*<<< orphan*/  ifnet_t ;
typedef  int /*<<< orphan*/  errno_t ;
typedef  int /*<<< orphan*/  einit ;

/* Variables and functions */
 int IFNET_INIT_ALLOC_KPI ; 
 int /*<<< orphan*/  IFNET_INIT_CURRENT_VERSION ; 
 int IFNET_INIT_LEGACY ; 
 int IFNET_INIT_NX_NOAUTO ; 
 int /*<<< orphan*/  bzero (struct ifnet_init_eparams*,int) ; 
 int /*<<< orphan*/  ifnet_allocate_extended (struct ifnet_init_eparams*,int /*<<< orphan*/ *) ; 

errno_t
ifnet_allocate_common(const struct ifnet_init_params *init,
    ifnet_t *ifp, bool is_internal)
{
	struct ifnet_init_eparams einit;

	bzero(&einit, sizeof (einit));

	einit.ver		= IFNET_INIT_CURRENT_VERSION;
	einit.len		= sizeof (einit);
	einit.flags		= IFNET_INIT_LEGACY | IFNET_INIT_NX_NOAUTO;
	if (!is_internal) {
		einit.flags |= IFNET_INIT_ALLOC_KPI;
	}
	einit.uniqueid		= init->uniqueid;
	einit.uniqueid_len	= init->uniqueid_len;
	einit.name		= init->name;
	einit.unit		= init->unit;
	einit.family		= init->family;
	einit.type		= init->type;
	einit.output		= init->output;
	einit.demux		= init->demux;
	einit.add_proto		= init->add_proto;
	einit.del_proto		= init->del_proto;
	einit.check_multi	= init->check_multi;
	einit.framer		= init->framer;
	einit.softc		= init->softc;
	einit.ioctl		= init->ioctl;
	einit.set_bpf_tap	= init->set_bpf_tap;
	einit.detach		= init->detach;
	einit.event		= init->event;
	einit.broadcast_addr	= init->broadcast_addr;
	einit.broadcast_len	= init->broadcast_len;

	return (ifnet_allocate_extended(&einit, ifp));
}