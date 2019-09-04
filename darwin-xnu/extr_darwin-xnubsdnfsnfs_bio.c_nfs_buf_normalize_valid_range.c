#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct nfsbuf {int nb_validoff; int nb_bufsize; int nb_validend; } ;
typedef  scalar_t__ off_t ;
typedef  TYPE_1__* nfsnode_t ;
struct TYPE_3__ {int n_size; } ;

/* Variables and functions */
 scalar_t__ NBOFF (struct nfsbuf*) ; 
 scalar_t__ NBPGVALID (struct nfsbuf*,int) ; 
 int PAGE_SIZE ; 

void
nfs_buf_normalize_valid_range(nfsnode_t np, struct nfsbuf *bp)
{
	int pg, npg;
	/* pull validoff back to start of contiguous valid page range */
	pg = bp->nb_validoff/PAGE_SIZE;
	while (pg >= 0 && NBPGVALID(bp,pg))
		pg--;
	bp->nb_validoff = (pg+1) * PAGE_SIZE;
	/* push validend forward to end of contiguous valid page range */
	npg = bp->nb_bufsize/PAGE_SIZE;
	pg = bp->nb_validend/PAGE_SIZE;
	while (pg < npg && NBPGVALID(bp,pg))
		pg++;
	bp->nb_validend = pg * PAGE_SIZE;
	/* clip to EOF */
	if (NBOFF(bp) + bp->nb_validend > (off_t)np->n_size)
		bp->nb_validend = np->n_size % bp->nb_bufsize;
}