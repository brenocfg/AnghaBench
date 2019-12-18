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
struct nfs_write_data {int /*<<< orphan*/ * ds_clp; struct nfs_pgio_header* header; } ;
struct nfs_pgio_header {int /*<<< orphan*/  inode; int /*<<< orphan*/ * dreq; } ;

/* Variables and functions */
 int /*<<< orphan*/  FMODE_READ ; 
 scalar_t__ nfs_have_delegation (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static
bool nfs4_write_need_cache_consistency_data(const struct nfs_write_data *data)
{
	const struct nfs_pgio_header *hdr = data->header;

	/* Don't request attributes for pNFS or O_DIRECT writes */
	if (data->ds_clp != NULL || hdr->dreq != NULL)
		return false;
	/* Otherwise, request attributes if and only if we don't hold
	 * a delegation
	 */
	return nfs_have_delegation(hdr->inode, FMODE_READ) == 0;
}