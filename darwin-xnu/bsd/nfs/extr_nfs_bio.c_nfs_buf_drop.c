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
struct nfsbuf {int /*<<< orphan*/  nb_lflags; } ;

/* Variables and functions */
 int /*<<< orphan*/  CLR (int /*<<< orphan*/ ,int) ; 
 scalar_t__ ISSET (int /*<<< orphan*/ ,int) ; 
 int NBL_BUSY ; 
 int NBL_WANTED ; 
 int /*<<< orphan*/  panic (char*) ; 
 int /*<<< orphan*/  wakeup (struct nfsbuf*) ; 

void
nfs_buf_drop(struct nfsbuf *bp)
{
	int need_wakeup = 0;

	if (!ISSET(bp->nb_lflags, NBL_BUSY))
		panic("nfs_buf_drop: buffer not busy!");
	if (ISSET(bp->nb_lflags, NBL_WANTED)) {
	        /* delay the actual wakeup until after we clear NBL_BUSY */
		need_wakeup = 1;
	}
	/* Unlock the buffer. */
	CLR(bp->nb_lflags, (NBL_BUSY | NBL_WANTED));

	if (need_wakeup)
	        wakeup(bp);
}