#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct vnet_port {int /*<<< orphan*/  vio; } ;
struct vnet_mcast_entry {int sent; struct vnet_mcast_entry* next; int /*<<< orphan*/  addr; scalar_t__ hit; } ;
struct vnet {struct vnet_mcast_entry* mcast_list; } ;
struct TYPE_2__ {int /*<<< orphan*/  sid; int /*<<< orphan*/  stype_env; int /*<<< orphan*/  stype; int /*<<< orphan*/  type; } ;
struct vio_net_mcast_info {int set; int count; int /*<<< orphan*/ * mcast_addr; TYPE_1__ tag; } ;
typedef  int /*<<< orphan*/  info ;

/* Variables and functions */
 int ETH_ALEN ; 
 int /*<<< orphan*/  VIO_SUBTYPE_INFO ; 
 int /*<<< orphan*/  VIO_TYPE_CTRL ; 
 int /*<<< orphan*/  VNET_MCAST_INFO ; 
 int VNET_NUM_MCAST ; 
 int /*<<< orphan*/  kfree (struct vnet_mcast_entry*) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  memset (struct vio_net_mcast_info*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  vio_ldc_send (int /*<<< orphan*/ *,struct vio_net_mcast_info*,int) ; 
 int /*<<< orphan*/  vio_send_sid (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void __send_mc_list(struct vnet *vp, struct vnet_port *port)
{
	struct vio_net_mcast_info info;
	struct vnet_mcast_entry *m, **pp;
	int n_addrs;

	memset(&info, 0, sizeof(info));

	info.tag.type = VIO_TYPE_CTRL;
	info.tag.stype = VIO_SUBTYPE_INFO;
	info.tag.stype_env = VNET_MCAST_INFO;
	info.tag.sid = vio_send_sid(&port->vio);
	info.set = 1;

	n_addrs = 0;
	for (m = vp->mcast_list; m; m = m->next) {
		if (m->sent)
			continue;
		m->sent = 1;
		memcpy(&info.mcast_addr[n_addrs * ETH_ALEN],
		       m->addr, ETH_ALEN);
		if (++n_addrs == VNET_NUM_MCAST) {
			info.count = n_addrs;

			(void) vio_ldc_send(&port->vio, &info,
					    sizeof(info));
			n_addrs = 0;
		}
	}
	if (n_addrs) {
		info.count = n_addrs;
		(void) vio_ldc_send(&port->vio, &info, sizeof(info));
	}

	info.set = 0;

	n_addrs = 0;
	pp = &vp->mcast_list;
	while ((m = *pp) != NULL) {
		if (m->hit) {
			m->hit = 0;
			pp = &m->next;
			continue;
		}

		memcpy(&info.mcast_addr[n_addrs * ETH_ALEN],
		       m->addr, ETH_ALEN);
		if (++n_addrs == VNET_NUM_MCAST) {
			info.count = n_addrs;
			(void) vio_ldc_send(&port->vio, &info,
					    sizeof(info));
			n_addrs = 0;
		}

		*pp = m->next;
		kfree(m);
	}
	if (n_addrs) {
		info.count = n_addrs;
		(void) vio_ldc_send(&port->vio, &info, sizeof(info));
	}
}