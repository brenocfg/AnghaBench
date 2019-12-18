#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u_char ;
struct TYPE_4__ {scalar_t__ count; scalar_t__ num; } ;
struct TYPE_3__ {scalar_t__ byte; } ;
struct nandsim {int state; TYPE_2__ regs; TYPE_1__ buf; } ;
struct nand_chip {scalar_t__ priv; } ;
struct mtd_info {scalar_t__ priv; } ;

/* Variables and functions */
 int /*<<< orphan*/  NS_DBG (char*,scalar_t__) ; 
 int /*<<< orphan*/  NS_ERR (char*,...) ; 
 int /*<<< orphan*/  NS_STATUS_FAILED (struct nandsim*) ; 
 int STATE_DATAIN_MASK ; 
 int /*<<< orphan*/  get_state_name (int) ; 
 int /*<<< orphan*/  memcpy (scalar_t__,int /*<<< orphan*/  const*,int) ; 
 int /*<<< orphan*/  switch_to_ready_state (struct nandsim*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void ns_nand_write_buf(struct mtd_info *mtd, const u_char *buf, int len)
{
        struct nandsim *ns = (struct nandsim *)((struct nand_chip *)mtd->priv)->priv;

	/* Check that chip is expecting data input */
	if (!(ns->state & STATE_DATAIN_MASK)) {
		NS_ERR("write_buf: data input isn't expected, state is %s, "
			"switch to STATE_READY\n", get_state_name(ns->state));
		switch_to_ready_state(ns, NS_STATUS_FAILED(ns));
		return;
	}

	/* Check if these are expected bytes */
	if (ns->regs.count + len > ns->regs.num) {
		NS_ERR("write_buf: too many input bytes\n");
		switch_to_ready_state(ns, NS_STATUS_FAILED(ns));
		return;
	}

	memcpy(ns->buf.byte + ns->regs.count, buf, len);
	ns->regs.count += len;

	if (ns->regs.count == ns->regs.num) {
		NS_DBG("write_buf: %d bytes were written\n", ns->regs.count);
	}
}