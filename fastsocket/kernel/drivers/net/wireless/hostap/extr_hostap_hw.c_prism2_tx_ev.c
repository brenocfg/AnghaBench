#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct net_device {int /*<<< orphan*/  name; } ;
struct hfa384x_tx_frame {scalar_t__ sw_support; int /*<<< orphan*/  duration_id; int /*<<< orphan*/  seq_ctrl; int /*<<< orphan*/  tx_rate; int /*<<< orphan*/  retry_count; int /*<<< orphan*/  status; } ;
struct TYPE_5__ {int frame_dump; struct net_device* dev; } ;
typedef  TYPE_1__ local_info_t ;

/* Variables and functions */
 int /*<<< orphan*/  DEBUG_EXTRA ; 
 int /*<<< orphan*/  HFA384X_EVACK_OFF ; 
 int /*<<< orphan*/  HFA384X_EV_TX ; 
 int /*<<< orphan*/  HFA384X_OUTW (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PDEBUG (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int PRISM2_DUMP_TX_HDR ; 
 int /*<<< orphan*/  hostap_tx_callback (TYPE_1__*,struct hfa384x_tx_frame*,int,char*) ; 
 scalar_t__ hostap_tx_compl_read (TYPE_1__*,int /*<<< orphan*/ ,struct hfa384x_tx_frame*,char**) ; 
 int /*<<< orphan*/  kfree (char*) ; 
 int /*<<< orphan*/  le16_to_cpu (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void prism2_tx_ev(local_info_t *local)
{
	struct net_device *dev = local->dev;
	char *payload = NULL;
	struct hfa384x_tx_frame txdesc;

	if (hostap_tx_compl_read(local, 0, &txdesc, &payload))
		goto fail;

	if (local->frame_dump & PRISM2_DUMP_TX_HDR) {
		PDEBUG(DEBUG_EXTRA, "%s: TX - status=0x%04x "
		       "retry_count=%d tx_rate=%d seq_ctrl=%d "
		       "duration_id=%d\n",
		       dev->name, le16_to_cpu(txdesc.status),
		       txdesc.retry_count, txdesc.tx_rate,
		       le16_to_cpu(txdesc.seq_ctrl),
		       le16_to_cpu(txdesc.duration_id));
	}

	if (txdesc.sw_support)
		hostap_tx_callback(local, &txdesc, 1, payload);
	kfree(payload);

 fail:
	HFA384X_OUTW(HFA384X_EV_TX, HFA384X_EVACK_OFF);
}