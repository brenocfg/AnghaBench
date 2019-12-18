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
struct nfs_pgio_header {int /*<<< orphan*/  lseg; } ;

/* Variables and functions */
 int /*<<< orphan*/  nfs_readhdr_free (struct nfs_pgio_header*) ; 
 int /*<<< orphan*/  put_lseg (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void pnfs_readhdr_free(struct nfs_pgio_header *hdr)
{
	put_lseg(hdr->lseg);
	nfs_readhdr_free(hdr);
}