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
typedef  int /*<<< orphan*/  u8 ;
typedef  int /*<<< orphan*/  u32 ;
struct fcoe_rport {int /*<<< orphan*/  enode_mac; } ;
struct fcoe_ctlr {struct fc_lport* lp; } ;
struct fc_rport_priv {int dummy; } ;
struct TYPE_2__ {struct fc_rport_priv* (* rport_lookup ) (struct fc_lport*,int /*<<< orphan*/ ) ;} ;
struct fc_lport {TYPE_1__ tt; } ;

/* Variables and functions */
 int /*<<< orphan*/  ETH_ALEN ; 
 struct fcoe_rport* fcoe_ctlr_rport (struct fc_rport_priv*) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rcu_read_lock () ; 
 int /*<<< orphan*/  rcu_read_unlock () ; 
 struct fc_rport_priv* stub1 (struct fc_lport*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int fcoe_ctlr_vn_lookup(struct fcoe_ctlr *fip, u32 port_id, u8 *mac)
{
	struct fc_lport *lport = fip->lp;
	struct fc_rport_priv *rdata;
	struct fcoe_rport *frport;
	int ret = -1;

	rcu_read_lock();
	rdata = lport->tt.rport_lookup(lport, port_id);
	if (rdata) {
		frport = fcoe_ctlr_rport(rdata);
		memcpy(mac, frport->enode_mac, ETH_ALEN);
		ret = 0;
	}
	rcu_read_unlock();
	return ret;
}