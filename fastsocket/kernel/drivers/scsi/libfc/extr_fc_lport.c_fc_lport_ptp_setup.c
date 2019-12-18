#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  void* u64 ;
typedef  int /*<<< orphan*/  u32 ;
struct TYPE_9__ {int /*<<< orphan*/  (* rport_login ) (TYPE_4__*) ;TYPE_4__* (* rport_create ) (struct fc_lport*,int /*<<< orphan*/ ) ;int /*<<< orphan*/  rport_destroy; int /*<<< orphan*/  (* rport_logoff ) (TYPE_4__*) ;} ;
struct TYPE_8__ {int /*<<< orphan*/  disc_mutex; } ;
struct fc_lport {TYPE_4__* ptp_rdata; TYPE_3__ tt; TYPE_2__ disc; } ;
struct TYPE_7__ {void* node_name; void* port_name; } ;
struct TYPE_10__ {TYPE_1__ ids; int /*<<< orphan*/  kref; } ;

/* Variables and functions */
 int /*<<< orphan*/  fc_lport_enter_ready (struct fc_lport*) ; 
 int /*<<< orphan*/  kref_get (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kref_put (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (TYPE_4__*) ; 
 TYPE_4__* stub2 (struct fc_lport*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub3 (TYPE_4__*) ; 

__attribute__((used)) static void fc_lport_ptp_setup(struct fc_lport *lport,
			       u32 remote_fid, u64 remote_wwpn,
			       u64 remote_wwnn)
{
	mutex_lock(&lport->disc.disc_mutex);
	if (lport->ptp_rdata) {
		lport->tt.rport_logoff(lport->ptp_rdata);
		kref_put(&lport->ptp_rdata->kref, lport->tt.rport_destroy);
	}
	lport->ptp_rdata = lport->tt.rport_create(lport, remote_fid);
	kref_get(&lport->ptp_rdata->kref);
	lport->ptp_rdata->ids.port_name = remote_wwpn;
	lport->ptp_rdata->ids.node_name = remote_wwnn;
	mutex_unlock(&lport->disc.disc_mutex);

	lport->tt.rport_login(lport->ptp_rdata);

	fc_lport_enter_ready(lport);
}