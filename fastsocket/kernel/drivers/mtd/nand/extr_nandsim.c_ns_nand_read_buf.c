#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u_char ;
struct TYPE_8__ {scalar_t__ count; scalar_t__ num; scalar_t__ row; } ;
struct TYPE_7__ {scalar_t__ pgnum; } ;
struct TYPE_6__ {scalar_t__ byte; } ;
struct TYPE_5__ {scalar_t__ cle; scalar_t__ ale; int /*<<< orphan*/  ce; } ;
struct nandsim {int state; int options; int nxstate; TYPE_4__ regs; TYPE_3__ geom; TYPE_2__ buf; TYPE_1__ lines; } ;
struct nand_chip {int /*<<< orphan*/  (* read_byte ) (struct mtd_info*) ;scalar_t__ priv; } ;
struct mtd_info {scalar_t__ priv; } ;

/* Variables and functions */
 int /*<<< orphan*/  ACTION_CPY ; 
 int /*<<< orphan*/  NS_DBG (char*,scalar_t__) ; 
 int /*<<< orphan*/  NS_ERR (char*) ; 
 scalar_t__ NS_STATE (int) ; 
 int /*<<< orphan*/  NS_STATUS_FAILED (struct nandsim*) ; 
 int /*<<< orphan*/  NS_WARN (char*,int /*<<< orphan*/ ) ; 
 int OPT_AUTOINCR ; 
 scalar_t__ STATE_DATAOUT ; 
 int STATE_DATAOUT_MASK ; 
 scalar_t__ STATE_READY ; 
 int /*<<< orphan*/  do_state_action (struct nandsim*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  get_state_name (int) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,scalar_t__,int) ; 
 int /*<<< orphan*/  stub1 (struct mtd_info*) ; 
 int /*<<< orphan*/  switch_state (struct nandsim*) ; 
 int /*<<< orphan*/  switch_to_ready_state (struct nandsim*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void ns_nand_read_buf(struct mtd_info *mtd, u_char *buf, int len)
{
        struct nandsim *ns = (struct nandsim *)((struct nand_chip *)mtd->priv)->priv;

	/* Sanity and correctness checks */
	if (!ns->lines.ce) {
		NS_ERR("read_buf: chip is disabled\n");
		return;
	}
	if (ns->lines.ale || ns->lines.cle) {
		NS_ERR("read_buf: ALE or CLE pin is high\n");
		return;
	}
	if (!(ns->state & STATE_DATAOUT_MASK)) {
		NS_WARN("read_buf: unexpected data output cycle, current state is %s\n",
			get_state_name(ns->state));
		return;
	}

	if (NS_STATE(ns->state) != STATE_DATAOUT) {
		int i;

		for (i = 0; i < len; i++)
			buf[i] = ((struct nand_chip *)mtd->priv)->read_byte(mtd);

		return;
	}

	/* Check if these are expected bytes */
	if (ns->regs.count + len > ns->regs.num) {
		NS_ERR("read_buf: too many bytes to read\n");
		switch_to_ready_state(ns, NS_STATUS_FAILED(ns));
		return;
	}

	memcpy(buf, ns->buf.byte + ns->regs.count, len);
	ns->regs.count += len;

	if (ns->regs.count == ns->regs.num) {
		if ((ns->options & OPT_AUTOINCR) && NS_STATE(ns->state) == STATE_DATAOUT) {
			ns->regs.count = 0;
			if (ns->regs.row + 1 < ns->geom.pgnum)
				ns->regs.row += 1;
			NS_DBG("read_buf: switch to the next page (%#x)\n", ns->regs.row);
			do_state_action(ns, ACTION_CPY);
		}
		else if (NS_STATE(ns->nxstate) == STATE_READY)
			switch_state(ns);
	}

	return;
}