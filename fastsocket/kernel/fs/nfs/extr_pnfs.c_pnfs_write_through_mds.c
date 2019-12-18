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
struct nfs_write_data {struct nfs_pgio_header* header; } ;
struct nfs_pgio_header {int /*<<< orphan*/  pages; int /*<<< orphan*/  flags; } ;
struct nfs_pageio_descriptor {int pg_recoalesce; int /*<<< orphan*/  pg_list; } ;

/* Variables and functions */
 int /*<<< orphan*/  NFS_IOHDR_REDO ; 
 int /*<<< orphan*/  list_splice_tail_init (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nfs_pageio_reset_write_mds (struct nfs_pageio_descriptor*) ; 
 int /*<<< orphan*/  nfs_writedata_release (struct nfs_write_data*) ; 
 int /*<<< orphan*/  test_and_set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
pnfs_write_through_mds(struct nfs_pageio_descriptor *desc,
		struct nfs_write_data *data)
{
	struct nfs_pgio_header *hdr = data->header;

	if (!test_and_set_bit(NFS_IOHDR_REDO, &hdr->flags)) {
		list_splice_tail_init(&hdr->pages, &desc->pg_list);
		nfs_pageio_reset_write_mds(desc);
		desc->pg_recoalesce = 1;
	}
	nfs_writedata_release(data);
}