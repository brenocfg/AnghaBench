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
typedef  scalar_t__ uint32_t ;
struct nfsbuf {scalar_t__ nb_bufsize; scalar_t__ nb_data; } ;
struct nfs_vattr {int dummy; } ;
struct nfs_dir_buf_header {int ndbh_count; scalar_t__ ndbh_entry_end; } ;

/* Variables and functions */

uint32_t
nfs_dir_buf_freespace(struct nfsbuf *bp, int rdirplus)
{
	struct nfs_dir_buf_header *ndbhp = (struct nfs_dir_buf_header*)bp->nb_data;
	uint32_t space;

	if (!ndbhp)
		return (0);
	space = bp->nb_bufsize - ndbhp->ndbh_entry_end;
	if (rdirplus)
		space -= ndbhp->ndbh_count * sizeof(struct nfs_vattr);
	return (space);
}