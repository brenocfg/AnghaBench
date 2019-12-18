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
struct ipsec_pcb {int /*<<< orphan*/  ipsec_pcb_lock; int /*<<< orphan*/  ipsec_input_chain_lock; int /*<<< orphan*/  ipsec_input_chain; } ;

/* Variables and functions */
 int /*<<< orphan*/  TAILQ_REMOVE (int /*<<< orphan*/ *,struct ipsec_pcb*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ipsec_chain ; 
 int /*<<< orphan*/  ipsec_head ; 
 int /*<<< orphan*/  ipsec_lck_grp ; 
 int /*<<< orphan*/  ipsec_lock ; 
 int /*<<< orphan*/  ipsec_pcb_zone ; 
 int /*<<< orphan*/  lck_mtx_destroy (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lck_mtx_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lck_mtx_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lck_rw_destroy (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mbuf_freem_list (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  zfree (int /*<<< orphan*/ ,struct ipsec_pcb*) ; 

__attribute__((used)) static inline void
ipsec_free_pcb(struct ipsec_pcb *pcb, bool in_list)
{
#if IPSEC_NEXUS
	mbuf_freem_list(pcb->ipsec_input_chain);
	lck_mtx_destroy(&pcb->ipsec_input_chain_lock, ipsec_lck_grp);
#endif // IPSEC_NEXUS
	lck_rw_destroy(&pcb->ipsec_pcb_lock, ipsec_lck_grp);
	if (in_list) {
		lck_mtx_lock(&ipsec_lock);
		TAILQ_REMOVE(&ipsec_head, pcb, ipsec_chain);
		lck_mtx_unlock(&ipsec_lock);
	}
	zfree(ipsec_pcb_zone, pcb);
}