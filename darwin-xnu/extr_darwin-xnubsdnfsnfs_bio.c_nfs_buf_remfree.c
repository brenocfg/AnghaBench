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
struct TYPE_2__ {scalar_t__ tqe_next; } ;
struct nfsbuf {TYPE_1__ nb_free; int /*<<< orphan*/  nb_flags; } ;

/* Variables and functions */
 scalar_t__ ISSET (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NB_DELWRI ; 
 int /*<<< orphan*/  NB_META ; 
 int /*<<< orphan*/  NFSBUFCNTCHK () ; 
 scalar_t__ NFSNOLIST ; 
 int /*<<< orphan*/  TAILQ_REMOVE (int /*<<< orphan*/ *,struct nfsbuf*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nb_free ; 
 int /*<<< orphan*/  nfsbufdelwri ; 
 int /*<<< orphan*/  nfsbufdelwricnt ; 
 int /*<<< orphan*/  nfsbuffree ; 
 int /*<<< orphan*/  nfsbuffreecnt ; 
 int /*<<< orphan*/  nfsbuffreemeta ; 
 int /*<<< orphan*/  nfsbuffreemetacnt ; 
 int /*<<< orphan*/  panic (char*) ; 

void
nfs_buf_remfree(struct nfsbuf *bp)
{
	if (bp->nb_free.tqe_next == NFSNOLIST)
		panic("nfsbuf not on free list");
	if (ISSET(bp->nb_flags, NB_DELWRI)) {
		nfsbufdelwricnt--;
		TAILQ_REMOVE(&nfsbufdelwri, bp, nb_free);
	} else if (ISSET(bp->nb_flags, NB_META)) {
		nfsbuffreemetacnt--;
		TAILQ_REMOVE(&nfsbuffreemeta, bp, nb_free);
	} else {
		nfsbuffreecnt--;
		TAILQ_REMOVE(&nfsbuffree, bp, nb_free);
	}
	bp->nb_free.tqe_next = NFSNOLIST;
	NFSBUFCNTCHK();
}