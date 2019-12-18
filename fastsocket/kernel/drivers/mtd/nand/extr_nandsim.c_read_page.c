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
struct TYPE_6__ {int /*<<< orphan*/  byte; } ;
struct TYPE_5__ {size_t row; int column; int off; } ;
struct TYPE_4__ {int pgszoob; } ;
struct nandsim {TYPE_3__ buf; TYPE_2__ regs; scalar_t__ cfile; TYPE_1__ geom; int /*<<< orphan*/ * pages_written; } ;
typedef  int ssize_t ;
typedef  int loff_t ;

/* Variables and functions */
 int /*<<< orphan*/  NS_DBG (char*,size_t,...) ; 
 int /*<<< orphan*/  NS_ERR (char*,size_t,long) ; 
 union ns_mem* NS_GET_PAGE (struct nandsim*) ; 
 int /*<<< orphan*/  NS_PAGE_BYTE_OFF (struct nandsim*) ; 
 int /*<<< orphan*/  do_bit_flips (struct nandsim*,int) ; 
 scalar_t__ do_read_error (struct nandsim*,int) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ ,int,int) ; 
 int read_file (struct nandsim*,scalar_t__,int /*<<< orphan*/ ,int,int*) ; 

__attribute__((used)) static void read_page(struct nandsim *ns, int num)
{
	union ns_mem *mypage;

	if (ns->cfile) {
		if (!ns->pages_written[ns->regs.row]) {
			NS_DBG("read_page: page %d not written\n", ns->regs.row);
			memset(ns->buf.byte, 0xFF, num);
		} else {
			loff_t pos;
			ssize_t tx;

			NS_DBG("read_page: page %d written, reading from %d\n",
				ns->regs.row, ns->regs.column + ns->regs.off);
			if (do_read_error(ns, num))
				return;
			pos = (loff_t)ns->regs.row * ns->geom.pgszoob + ns->regs.column + ns->regs.off;
			tx = read_file(ns, ns->cfile, ns->buf.byte, num, &pos);
			if (tx != num) {
				NS_ERR("read_page: read error for page %d ret %ld\n", ns->regs.row, (long)tx);
				return;
			}
			do_bit_flips(ns, num);
		}
		return;
	}

	mypage = NS_GET_PAGE(ns);
	if (mypage->byte == NULL) {
		NS_DBG("read_page: page %d not allocated\n", ns->regs.row);
		memset(ns->buf.byte, 0xFF, num);
	} else {
		NS_DBG("read_page: page %d allocated, reading from %d\n",
			ns->regs.row, ns->regs.column + ns->regs.off);
		if (do_read_error(ns, num))
			return;
		memcpy(ns->buf.byte, NS_PAGE_BYTE_OFF(ns), num);
		do_bit_flips(ns, num);
	}
}