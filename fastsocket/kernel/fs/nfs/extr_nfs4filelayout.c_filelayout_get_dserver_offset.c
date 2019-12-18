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
struct pnfs_layout_segment {int dummy; } ;
struct nfs4_filelayout_segment {int stripe_type; } ;
typedef  int /*<<< orphan*/  loff_t ;

/* Variables and functions */
 int /*<<< orphan*/  BUG () ; 
 struct nfs4_filelayout_segment* FILELAYOUT_LSEG (struct pnfs_layout_segment*) ; 
#define  STRIPE_DENSE 129 
#define  STRIPE_SPARSE 128 
 int /*<<< orphan*/  filelayout_get_dense_offset (struct nfs4_filelayout_segment*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static loff_t
filelayout_get_dserver_offset(struct pnfs_layout_segment *lseg, loff_t offset)
{
	struct nfs4_filelayout_segment *flseg = FILELAYOUT_LSEG(lseg);

	switch (flseg->stripe_type) {
	case STRIPE_SPARSE:
		return offset;

	case STRIPE_DENSE:
		return filelayout_get_dense_offset(flseg, offset);
	}

	BUG();
}