#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_18__   TYPE_9__ ;
typedef  struct TYPE_17__   TYPE_8__ ;
typedef  struct TYPE_16__   TYPE_7__ ;
typedef  struct TYPE_15__   TYPE_6__ ;
typedef  struct TYPE_14__   TYPE_5__ ;
typedef  struct TYPE_13__   TYPE_4__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint32_t ;
struct TYPE_10__ {int /*<<< orphan*/  timestamp; } ;
struct TYPE_11__ {TYPE_1__ probe_resp; } ;
struct ieee80211_mgmt {TYPE_2__ u; } ;
struct dma_desc {int dummy; } ;
struct TYPE_15__ {size_t queue; int /*<<< orphan*/  fill_in_tsf; } ;
struct TYPE_17__ {int /*<<< orphan*/  i3e; } ;
struct TYPE_16__ {TYPE_8__ data; } ;
struct carl9170_tx_superframe {TYPE_6__ s; TYPE_7__ f; } ;
struct TYPE_14__ {int /*<<< orphan*/ * tx_queue; } ;
struct TYPE_12__ {scalar_t__ state; } ;
struct TYPE_13__ {TYPE_3__ psm; } ;
struct TYPE_18__ {TYPE_5__ wlan; TYPE_4__ phy; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 scalar_t__ CARL9170_PSM_WAKE ; 
 int /*<<< orphan*/  dma_put (int /*<<< orphan*/ *,struct dma_desc*) ; 
 TYPE_9__ fw ; 
 struct carl9170_tx_superframe* get_super (struct dma_desc*) ; 
 int /*<<< orphan*/  read_tsf (int /*<<< orphan*/ *) ; 
 scalar_t__ unlikely (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wlan_tx_ampdu (struct carl9170_tx_superframe*) ; 

__attribute__((used)) static void __wlan_tx(struct dma_desc *desc)
{
	struct carl9170_tx_superframe *super = get_super(desc);

	if (unlikely(super->s.fill_in_tsf)) {
		struct ieee80211_mgmt *mgmt = (void *) &super->f.data.i3e;
		uint32_t *tsf = (uint32_t *) &mgmt->u.probe_resp.timestamp;

		/*
		 * Truth be told: this is a hack.
		 *
		 * The *real* TSF is definitely going to be higher/older.
		 * But this hardware emulation code is head and shoulders
		 * above anything a driver can possibly do.
		 *
		 * (even, if it's got an accurate atomic clock source).
		 */

		read_tsf(tsf);
	}

	wlan_tx_ampdu(super);

#ifdef CONFIG_CARL9170FW_DEBUG
	BUG_ON(fw.phy.psm.state != CARL9170_PSM_WAKE);
#endif /* CONFIG_CARL9170FW_DEBUG */

	/* insert desc into the right queue */
	dma_put(&fw.wlan.tx_queue[super->s.queue], desc);
}