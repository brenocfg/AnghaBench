#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_6__ ;
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {int /*<<< orphan*/  sa_family; int /*<<< orphan*/  sa_data; } ;
union iwreq_data {TYPE_4__ addr; } ;
struct airo_info {int* fids; TYPE_6__* dev; TYPE_2__* txfids; } ;
typedef  size_t s32 ;
typedef  int /*<<< orphan*/  __le16 ;
struct TYPE_7__ {int /*<<< orphan*/  status; } ;
struct TYPE_11__ {TYPE_1__ ctlhdr; } ;
typedef  TYPE_5__ WifiCtlHdr ;
struct TYPE_9__ {int /*<<< orphan*/  tx_carrier_errors; int /*<<< orphan*/  tx_heartbeat_errors; int /*<<< orphan*/  tx_aborted_errors; } ;
struct TYPE_12__ {TYPE_3__ stats; } ;
struct TYPE_8__ {scalar_t__ virtual_host_addr; } ;

/* Variables and functions */
 int /*<<< orphan*/  ARPHRD_ETHER ; 
 int /*<<< orphan*/  BAP0 ; 
 int /*<<< orphan*/  ETH_ALEN ; 
 int /*<<< orphan*/  IWEVTXDROP ; 
 scalar_t__ SUCCESS ; 
 int /*<<< orphan*/  bap_read (struct airo_info*,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 scalar_t__ bap_setup (struct airo_info*,int,int,int /*<<< orphan*/ ) ; 
 int le16_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wireless_send_event (TYPE_6__*,int /*<<< orphan*/ ,union iwreq_data*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void get_tx_error(struct airo_info *ai, s32 fid)
{
	__le16 status;

	if (fid < 0)
		status = ((WifiCtlHdr *)ai->txfids[0].virtual_host_addr)->ctlhdr.status;
	else {
		if (bap_setup(ai, ai->fids[fid] & 0xffff, 4, BAP0) != SUCCESS)
			return;
		bap_read(ai, &status, 2, BAP0);
	}
	if (le16_to_cpu(status) & 2) /* Too many retries */
		ai->dev->stats.tx_aborted_errors++;
	if (le16_to_cpu(status) & 4) /* Transmit lifetime exceeded */
		ai->dev->stats.tx_heartbeat_errors++;
	if (le16_to_cpu(status) & 8) /* Aid fail */
		{ }
	if (le16_to_cpu(status) & 0x10) /* MAC disabled */
		ai->dev->stats.tx_carrier_errors++;
	if (le16_to_cpu(status) & 0x20) /* Association lost */
		{ }
	/* We produce a TXDROP event only for retry or lifetime
	 * exceeded, because that's the only status that really mean
	 * that this particular node went away.
	 * Other errors means that *we* screwed up. - Jean II */
	if ((le16_to_cpu(status) & 2) ||
	     (le16_to_cpu(status) & 4)) {
		union iwreq_data	wrqu;
		char junk[0x18];

		/* Faster to skip over useless data than to do
		 * another bap_setup(). We are at offset 0x6 and
		 * need to go to 0x18 and read 6 bytes - Jean II */
		bap_read(ai, (__le16 *) junk, 0x18, BAP0);

		/* Copy 802.11 dest address.
		 * We use the 802.11 header because the frame may
		 * not be 802.3 or may be mangled...
		 * In Ad-Hoc mode, it will be the node address.
		 * In managed mode, it will be most likely the AP addr
		 * User space will figure out how to convert it to
		 * whatever it needs (IP address or else).
		 * - Jean II */
		memcpy(wrqu.addr.sa_data, junk + 0x12, ETH_ALEN);
		wrqu.addr.sa_family = ARPHRD_ETHER;

		/* Send event to user space */
		wireless_send_event(ai->dev, IWEVTXDROP, &wrqu, NULL);
	}
}