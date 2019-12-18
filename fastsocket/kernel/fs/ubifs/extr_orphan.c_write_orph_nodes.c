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
struct ubifs_info {scalar_t__ cmt_orphans; int ohead_lnum; int orph_last; } ;

/* Variables and functions */
 int ubifs_leb_unmap (struct ubifs_info*,int) ; 
 int write_orph_node (struct ubifs_info*,int) ; 

__attribute__((used)) static int write_orph_nodes(struct ubifs_info *c, int atomic)
{
	int err;

	while (c->cmt_orphans > 0) {
		err = write_orph_node(c, atomic);
		if (err)
			return err;
	}
	if (atomic) {
		int lnum;

		/* Unmap any unused LEBs after consolidation */
		lnum = c->ohead_lnum + 1;
		for (lnum = c->ohead_lnum + 1; lnum <= c->orph_last; lnum++) {
			err = ubifs_leb_unmap(c, lnum);
			if (err)
				return err;
		}
	}
	return 0;
}