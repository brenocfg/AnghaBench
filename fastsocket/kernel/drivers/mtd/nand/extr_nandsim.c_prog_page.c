#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
union ns_mem {int /*<<< orphan*/ * byte; } ;
typedef  int /*<<< orphan*/  u_char ;
struct TYPE_6__ {int /*<<< orphan*/ * byte; } ;
struct TYPE_5__ {int pgszoob; } ;
struct TYPE_4__ {size_t row; int column; int off; } ;
struct nandsim {int* pages_written; TYPE_3__ buf; TYPE_2__ geom; TYPE_1__ regs; int /*<<< orphan*/  nand_pages_slab; scalar_t__ cfile; int /*<<< orphan*/ * file_buf; } ;
typedef  int ssize_t ;
typedef  int loff_t ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_NOFS ; 
 int /*<<< orphan*/  NS_DBG (char*,size_t) ; 
 int /*<<< orphan*/  NS_ERR (char*,size_t,...) ; 
 union ns_mem* NS_GET_PAGE (struct nandsim*) ; 
 int /*<<< orphan*/ * NS_PAGE_BYTE_OFF (struct nandsim*) ; 
 int /*<<< orphan*/ * kmem_cache_alloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int,int) ; 
 int read_file (struct nandsim*,scalar_t__,int /*<<< orphan*/ *,int,int*) ; 
 int write_file (struct nandsim*,scalar_t__,int /*<<< orphan*/ *,int,int*) ; 

__attribute__((used)) static int prog_page(struct nandsim *ns, int num)
{
	int i;
	union ns_mem *mypage;
	u_char *pg_off;

	if (ns->cfile) {
		loff_t off, pos;
		ssize_t tx;
		int all;

		NS_DBG("prog_page: writing page %d\n", ns->regs.row);
		pg_off = ns->file_buf + ns->regs.column + ns->regs.off;
		off = (loff_t)ns->regs.row * ns->geom.pgszoob + ns->regs.column + ns->regs.off;
		if (!ns->pages_written[ns->regs.row]) {
			all = 1;
			memset(ns->file_buf, 0xff, ns->geom.pgszoob);
		} else {
			all = 0;
			pos = off;
			tx = read_file(ns, ns->cfile, pg_off, num, &pos);
			if (tx != num) {
				NS_ERR("prog_page: read error for page %d ret %ld\n", ns->regs.row, (long)tx);
				return -1;
			}
		}
		for (i = 0; i < num; i++)
			pg_off[i] &= ns->buf.byte[i];
		if (all) {
			pos = (loff_t)ns->regs.row * ns->geom.pgszoob;
			tx = write_file(ns, ns->cfile, ns->file_buf, ns->geom.pgszoob, &pos);
			if (tx != ns->geom.pgszoob) {
				NS_ERR("prog_page: write error for page %d ret %ld\n", ns->regs.row, (long)tx);
				return -1;
			}
			ns->pages_written[ns->regs.row] = 1;
		} else {
			pos = off;
			tx = write_file(ns, ns->cfile, pg_off, num, &pos);
			if (tx != num) {
				NS_ERR("prog_page: write error for page %d ret %ld\n", ns->regs.row, (long)tx);
				return -1;
			}
		}
		return 0;
	}

	mypage = NS_GET_PAGE(ns);
	if (mypage->byte == NULL) {
		NS_DBG("prog_page: allocating page %d\n", ns->regs.row);
		/*
		 * We allocate memory with GFP_NOFS because a flash FS may
		 * utilize this. If it is holding an FS lock, then gets here,
		 * then kernel memory alloc runs writeback which goes to the FS
		 * again and deadlocks. This was seen in practice.
		 */
		mypage->byte = kmem_cache_alloc(ns->nand_pages_slab, GFP_NOFS);
		if (mypage->byte == NULL) {
			NS_ERR("prog_page: error allocating memory for page %d\n", ns->regs.row);
			return -1;
		}
		memset(mypage->byte, 0xFF, ns->geom.pgszoob);
	}

	pg_off = NS_PAGE_BYTE_OFF(ns);
	for (i = 0; i < num; i++)
		pg_off[i] &= ns->buf.byte[i];

	return 0;
}