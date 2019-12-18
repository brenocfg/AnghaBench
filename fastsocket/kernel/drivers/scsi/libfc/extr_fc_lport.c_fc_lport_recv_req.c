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
struct fc_seq {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* exch_done ) (struct fc_seq*) ;} ;
struct fc_lport {TYPE_1__ tt; } ;
struct fc_frame_header {size_t fh_type; } ;
struct fc_frame {int dummy; } ;
struct fc4_prov {int /*<<< orphan*/  module; int /*<<< orphan*/  (* recv ) (struct fc_lport*,struct fc_frame*) ;} ;

/* Variables and functions */
 size_t FC_FC4_PROV_SIZE ; 
 int /*<<< orphan*/  FC_LPORT_DBG (struct fc_lport*,char*,size_t) ; 
 int /*<<< orphan*/  fc_frame_free (struct fc_frame*) ; 
 struct fc_frame_header* fc_frame_header_get (struct fc_frame*) ; 
 int /*<<< orphan*/ * fc_passive_prov ; 
 struct fc_seq* fr_seq (struct fc_frame*) ; 
 int /*<<< orphan*/  module_put (int /*<<< orphan*/ ) ; 
 struct fc4_prov* rcu_dereference (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rcu_read_lock () ; 
 int /*<<< orphan*/  rcu_read_unlock () ; 
 int /*<<< orphan*/  stub1 (struct fc_lport*,struct fc_frame*) ; 
 int /*<<< orphan*/  stub2 (struct fc_seq*) ; 
 int /*<<< orphan*/  try_module_get (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void fc_lport_recv_req(struct fc_lport *lport,
			      struct fc_frame *fp)
{
	struct fc_frame_header *fh = fc_frame_header_get(fp);
	struct fc_seq *sp = fr_seq(fp);
	struct fc4_prov *prov;

	/*
	 * Use RCU read lock and module_lock to be sure module doesn't
	 * deregister and get unloaded while we're calling it.
	 * try_module_get() is inlined and accepts a NULL parameter.
	 * Only ELSes and FCP target ops should come through here.
	 * The locking is unfortunate, and a better scheme is being sought.
	 */

	rcu_read_lock();
	if (fh->fh_type >= FC_FC4_PROV_SIZE)
		goto drop;
	prov = rcu_dereference(fc_passive_prov[fh->fh_type]);
	if (!prov || !try_module_get(prov->module))
		goto drop;
	rcu_read_unlock();
	prov->recv(lport, fp);
	module_put(prov->module);
	return;
drop:
	rcu_read_unlock();
	FC_LPORT_DBG(lport, "dropping unexpected frame type %x\n", fh->fh_type);
	fc_frame_free(fp);
	lport->tt.exch_done(sp);
}