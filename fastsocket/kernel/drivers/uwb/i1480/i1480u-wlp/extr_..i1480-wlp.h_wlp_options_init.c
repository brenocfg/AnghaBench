#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  prid; } ;
struct wlp_options {TYPE_1__ def_tx_hdr; int /*<<< orphan*/  mutex; } ;

/* Variables and functions */
 int /*<<< orphan*/  UWB_ACK_INM ; 
 int /*<<< orphan*/  UWB_PHY_RATE_480 ; 
 int /*<<< orphan*/  cpu_to_le16 (int) ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wlp_tx_hdr_set_ack_policy (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wlp_tx_hdr_set_phy_rate (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wlp_tx_hdr_set_rts_cts (TYPE_1__*,int) ; 

__attribute__((used)) static inline
void wlp_options_init(struct wlp_options *options)
{
	mutex_init(&options->mutex);
	wlp_tx_hdr_set_ack_policy(&options->def_tx_hdr, UWB_ACK_INM);
	wlp_tx_hdr_set_rts_cts(&options->def_tx_hdr, 1);
	/* FIXME: default to phy caps */
	wlp_tx_hdr_set_phy_rate(&options->def_tx_hdr, UWB_PHY_RATE_480);
#ifndef WLP_HDR_FMT_2
	options->def_tx_hdr.prid = cpu_to_le16(0x0000);
#endif
}