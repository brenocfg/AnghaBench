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
struct il_rxon_cmd {scalar_t__ channel; } ;
struct il_csa_notification {scalar_t__ channel; int /*<<< orphan*/  status; } ;
struct TYPE_3__ {struct il_csa_notification csa_notif; } ;
struct il_rx_pkt {TYPE_1__ u; } ;
struct il_rx_buf {int dummy; } ;
struct TYPE_4__ {scalar_t__ channel; } ;
struct il_priv {scalar_t__ switch_channel; TYPE_2__ staging; int /*<<< orphan*/  status; int /*<<< orphan*/  active; } ;

/* Variables and functions */
 int /*<<< orphan*/  D_11H (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IL_ERR (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  S_CHANNEL_SWITCH_PENDING ; 
 int /*<<< orphan*/  il_chswitch_done (struct il_priv*,int) ; 
 int /*<<< orphan*/  le16_to_cpu (scalar_t__) ; 
 int /*<<< orphan*/  le32_to_cpu (int /*<<< orphan*/ ) ; 
 struct il_rx_pkt* rxb_addr (struct il_rx_buf*) ; 
 int /*<<< orphan*/  test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

void
il_hdl_csa(struct il_priv *il, struct il_rx_buf *rxb)
{
	struct il_rx_pkt *pkt = rxb_addr(rxb);
	struct il_csa_notification *csa = &(pkt->u.csa_notif);
	struct il_rxon_cmd *rxon = (void *)&il->active;

	if (!test_bit(S_CHANNEL_SWITCH_PENDING, &il->status))
		return;

	if (!le32_to_cpu(csa->status) && csa->channel == il->switch_channel) {
		rxon->channel = csa->channel;
		il->staging.channel = csa->channel;
		D_11H("CSA notif: channel %d\n", le16_to_cpu(csa->channel));
		il_chswitch_done(il, true);
	} else {
		IL_ERR("CSA notif (fail) : channel %d\n",
		       le16_to_cpu(csa->channel));
		il_chswitch_done(il, false);
	}
}