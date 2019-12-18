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
struct cxgbi_sock {scalar_t__ wr_cred; scalar_t__ wr_max_cred; int /*<<< orphan*/ * cdev; int /*<<< orphan*/ * dst; int /*<<< orphan*/  tid; int /*<<< orphan*/  flags; int /*<<< orphan*/  state; } ;
struct cxgb4_lld_info {int /*<<< orphan*/  tids; } ;

/* Variables and functions */
 int /*<<< orphan*/  CTPF_HAS_ATID ; 
 int /*<<< orphan*/  CTPF_HAS_TID ; 
 int CXGBI_DBG_SOCK ; 
 int CXGBI_DBG_TOE ; 
 int /*<<< orphan*/  cxgb4_remove_tid (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct cxgb4_lld_info* cxgbi_cdev_priv (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cxgbi_sock_clear_flag (struct cxgbi_sock*,int /*<<< orphan*/ ) ; 
 scalar_t__ cxgbi_sock_flag (struct cxgbi_sock*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cxgbi_sock_free_cpl_skbs (struct cxgbi_sock*) ; 
 int /*<<< orphan*/  cxgbi_sock_purge_wr_queue (struct cxgbi_sock*) ; 
 int /*<<< orphan*/  cxgbi_sock_put (struct cxgbi_sock*) ; 
 int /*<<< orphan*/  cxgbi_sock_reset_wr_list (struct cxgbi_sock*) ; 
 int /*<<< orphan*/  free_atid (struct cxgbi_sock*) ; 
 int /*<<< orphan*/  l2t_put (struct cxgbi_sock*) ; 
 int /*<<< orphan*/  log_debug (int,char*,struct cxgbi_sock*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void release_offload_resources(struct cxgbi_sock *csk)
{
	struct cxgb4_lld_info *lldi;

	log_debug(1 << CXGBI_DBG_TOE | 1 << CXGBI_DBG_SOCK,
		"csk 0x%p,%u,0x%lx,%u.\n",
		csk, csk->state, csk->flags, csk->tid);

	cxgbi_sock_free_cpl_skbs(csk);
	if (csk->wr_cred != csk->wr_max_cred) {
		cxgbi_sock_purge_wr_queue(csk);
		cxgbi_sock_reset_wr_list(csk);
	}

	l2t_put(csk);
	if (cxgbi_sock_flag(csk, CTPF_HAS_ATID))
		free_atid(csk);
	else if (cxgbi_sock_flag(csk, CTPF_HAS_TID)) {
		lldi = cxgbi_cdev_priv(csk->cdev);
		cxgb4_remove_tid(lldi->tids, 0, csk->tid);
		cxgbi_sock_clear_flag(csk, CTPF_HAS_TID);
		cxgbi_sock_put(csk);
	}
	csk->dst = NULL;
	csk->cdev = NULL;
}