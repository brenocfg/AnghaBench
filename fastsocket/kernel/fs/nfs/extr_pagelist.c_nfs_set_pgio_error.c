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
struct nfs_pgio_header {scalar_t__ io_start; scalar_t__ good_bytes; int error; int /*<<< orphan*/  lock; int /*<<< orphan*/  flags; } ;
typedef  scalar_t__ loff_t ;

/* Variables and functions */
 int /*<<< orphan*/  NFS_IOHDR_EOF ; 
 int /*<<< orphan*/  NFS_IOHDR_ERROR ; 
 int /*<<< orphan*/  clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

void nfs_set_pgio_error(struct nfs_pgio_header *hdr, int error, loff_t pos)
{
	spin_lock(&hdr->lock);
	if (pos < hdr->io_start + hdr->good_bytes) {
		set_bit(NFS_IOHDR_ERROR, &hdr->flags);
		clear_bit(NFS_IOHDR_EOF, &hdr->flags);
		hdr->good_bytes = pos - hdr->io_start;
		hdr->error = error;
	}
	spin_unlock(&hdr->lock);
}