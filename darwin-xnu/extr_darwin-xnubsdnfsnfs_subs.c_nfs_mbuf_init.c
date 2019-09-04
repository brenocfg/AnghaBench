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
struct mbuf_stat {int /*<<< orphan*/  minclsize; int /*<<< orphan*/  mhlen; } ;

/* Variables and functions */
 int /*<<< orphan*/  mbuf_stats (struct mbuf_stat*) ; 
 int /*<<< orphan*/  nfs_mbuf_mhlen ; 
 int /*<<< orphan*/  nfs_mbuf_minclsize ; 

void
nfs_mbuf_init(void)
{
	struct mbuf_stat ms;

	mbuf_stats(&ms);
	nfs_mbuf_mhlen = ms.mhlen;
	nfs_mbuf_minclsize = ms.minclsize;
}