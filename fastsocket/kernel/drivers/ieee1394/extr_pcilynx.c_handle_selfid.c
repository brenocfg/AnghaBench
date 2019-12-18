#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int /*<<< orphan*/  reg_1394a; } ;
struct ti_lynx {int phy_reg0; int selfid_size; TYPE_1__ phyic; int /*<<< orphan*/  id; int /*<<< orphan*/ * rcv_page; } ;
struct selfid {int phy_id; int /*<<< orphan*/  extended; } ;
struct hpsb_host {scalar_t__ in_bus_reset; } ;
typedef  int /*<<< orphan*/  quadlet_t ;

/* Variables and functions */
 int /*<<< orphan*/  KERN_DEBUG ; 
 int /*<<< orphan*/  KERN_INFO ; 
 int /*<<< orphan*/  LINK_CONTROL ; 
 int LINK_CONTROL_CYCMASTER ; 
 int LINK_CONTROL_CYCTIMEREN ; 
 int LINK_CONTROL_RCV_CMP_VALID ; 
 int LINK_CONTROL_RX_ASYNC_EN ; 
 int LINK_CONTROL_TX_ASYNC_EN ; 
 int /*<<< orphan*/  LINK_ID ; 
 int /*<<< orphan*/  PRINT (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int,...) ; 
 int /*<<< orphan*/  cpu_to_be32s (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  generate_own_selfid (struct ti_lynx*,struct hpsb_host*) ; 
 int /*<<< orphan*/  hpsb_selfid_complete (struct hpsb_host*,int,int) ; 
 int /*<<< orphan*/  hpsb_selfid_received (struct hpsb_host*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  reg_set_bits (struct ti_lynx*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  reg_write (struct ti_lynx*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void handle_selfid(struct ti_lynx *lynx, struct hpsb_host *host)
{
        quadlet_t *q = lynx->rcv_page;
        int phyid, isroot, size;
        quadlet_t lsid = 0;
        int i;

        if (lynx->phy_reg0 == -1 || lynx->selfid_size == -1) return;

        size = lynx->selfid_size;
        phyid = lynx->phy_reg0;

        i = (size > 16 ? 16 : size) / 4 - 1;
        while (i >= 0) {
                cpu_to_be32s(&q[i]);
                i--;
        }

        if (!lynx->phyic.reg_1394a) {
                lsid = generate_own_selfid(lynx, host);
        }

        isroot = (phyid & 2) != 0;
        phyid >>= 2;
        PRINT(KERN_INFO, lynx->id, "SelfID process finished (phyid %d, %s)",
              phyid, (isroot ? "root" : "not root"));
        reg_write(lynx, LINK_ID, (0xffc0 | phyid) << 16);

        if (!lynx->phyic.reg_1394a && !size) {
                hpsb_selfid_received(host, lsid);
        }

        while (size > 0) {
                struct selfid *sid = (struct selfid *)q;

                if (!lynx->phyic.reg_1394a && !sid->extended
                    && (sid->phy_id == (phyid + 1))) {
                        hpsb_selfid_received(host, lsid);
                }

                if (q[0] == ~q[1]) {
                        PRINT(KERN_DEBUG, lynx->id, "SelfID packet 0x%x rcvd",
                              q[0]);
                        hpsb_selfid_received(host, q[0]);
                } else {
                        PRINT(KERN_INFO, lynx->id,
                              "inconsistent selfid 0x%x/0x%x", q[0], q[1]);
                }
                q += 2;
                size -= 8;
        }

        if (!lynx->phyic.reg_1394a && isroot && phyid != 0) {
                hpsb_selfid_received(host, lsid);
        }

        hpsb_selfid_complete(host, phyid, isroot);

        if (host->in_bus_reset) return; /* in bus reset again */

        if (isroot) reg_set_bits(lynx, LINK_CONTROL, LINK_CONTROL_CYCMASTER); //FIXME: I do not think, we need this here
        reg_set_bits(lynx, LINK_CONTROL,
                     LINK_CONTROL_RCV_CMP_VALID | LINK_CONTROL_TX_ASYNC_EN
                     | LINK_CONTROL_RX_ASYNC_EN | LINK_CONTROL_CYCTIMEREN);
}