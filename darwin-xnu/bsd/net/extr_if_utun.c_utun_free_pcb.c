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
struct utun_pcb {int /*<<< orphan*/  utun_pcb_lock; int /*<<< orphan*/  utun_input_chain_lock; int /*<<< orphan*/  utun_input_chain; } ;

/* Variables and functions */
 int /*<<< orphan*/  TAILQ_REMOVE (int /*<<< orphan*/ *,struct utun_pcb*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lck_mtx_destroy (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lck_mtx_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lck_mtx_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lck_rw_destroy (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mbuf_freem_list (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  utun_chain ; 
 int /*<<< orphan*/  utun_head ; 
 int /*<<< orphan*/  utun_lck_grp ; 
 int /*<<< orphan*/  utun_lock ; 
 int /*<<< orphan*/  utun_pcb_zone ; 
 int /*<<< orphan*/  zfree (int /*<<< orphan*/ ,struct utun_pcb*) ; 

__attribute__((used)) static inline void
utun_free_pcb(struct utun_pcb *pcb, bool in_list)
{
#ifdef UTUN_NEXUS
	mbuf_freem_list(pcb->utun_input_chain);
	lck_mtx_destroy(&pcb->utun_input_chain_lock, utun_lck_grp);
#endif // UTUN_NEXUS
	lck_rw_destroy(&pcb->utun_pcb_lock, utun_lck_grp);
	if (in_list) {
		lck_mtx_lock(&utun_lock);
		TAILQ_REMOVE(&utun_head, pcb, utun_chain);
		lck_mtx_unlock(&utun_lock);
	}
	zfree(utun_pcb_zone, pcb);
}