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
struct pf_vf_bulletin_content {scalar_t__ version; scalar_t__ crc; int valid_bitmap; int /*<<< orphan*/  vlan; int /*<<< orphan*/ * mac; } ;
struct bnx2x {struct pf_vf_bulletin_content old_bulletin; TYPE_2__* dev; TYPE_1__* pf2vf_bulletin; } ;
typedef  enum sample_bulletin_result { ____Placeholder_sample_bulletin_result } sample_bulletin_result ;
struct TYPE_4__ {int /*<<< orphan*/ * dev_addr; } ;
struct TYPE_3__ {struct pf_vf_bulletin_content content; } ;

/* Variables and functions */
 int /*<<< orphan*/  BNX2X_ERR (char*,int,...) ; 
 int BULLETIN_ATTEMPTS ; 
 int /*<<< orphan*/  ETH_ALEN ; 
 int MAC_ADDR_VALID ; 
 int PFVF_BULLETIN_CRC_ERR ; 
 int PFVF_BULLETIN_UNCHANGED ; 
 int PFVF_BULLETIN_UPDATED ; 
 int /*<<< orphan*/  VLAN_HLEN ; 
 int VLAN_VALID ; 
 scalar_t__ bnx2x_crc_vf_bulletin (struct bnx2x*,struct pf_vf_bulletin_content*) ; 
 scalar_t__ memcmp (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

enum sample_bulletin_result bnx2x_sample_bulletin(struct bnx2x *bp)
{
	struct pf_vf_bulletin_content bulletin = bp->pf2vf_bulletin->content;
	int attempts;

	/* bulletin board hasn't changed since last sample */
	if (bp->old_bulletin.version == bulletin.version)
		return PFVF_BULLETIN_UNCHANGED;

	/* validate crc of new bulletin board */
	if (bp->old_bulletin.version != bp->pf2vf_bulletin->content.version) {
		/* sampling structure in mid post may result with corrupted data
		 * validate crc to ensure coherency.
		 */
		for (attempts = 0; attempts < BULLETIN_ATTEMPTS; attempts++) {
			bulletin = bp->pf2vf_bulletin->content;
			if (bulletin.crc == bnx2x_crc_vf_bulletin(bp,
								  &bulletin))
				break;
			BNX2X_ERR("bad crc on bulletin board. Contained %x computed %x\n",
				  bulletin.crc,
				  bnx2x_crc_vf_bulletin(bp, &bulletin));
		}
		if (attempts >= BULLETIN_ATTEMPTS) {
			BNX2X_ERR("pf to vf bulletin board crc was wrong %d consecutive times. Aborting\n",
				  attempts);
			return PFVF_BULLETIN_CRC_ERR;
		}
	}

	/* the mac address in bulletin board is valid and is new */
	if (bulletin.valid_bitmap & 1 << MAC_ADDR_VALID &&
	    memcmp(bulletin.mac, bp->old_bulletin.mac, ETH_ALEN)) {
		/* update new mac to net device */
		memcpy(bp->dev->dev_addr, bulletin.mac, ETH_ALEN);
	}

	/* the vlan in bulletin board is valid and is new */
	if (bulletin.valid_bitmap & 1 << VLAN_VALID)
		memcpy(&bulletin.vlan, &bp->old_bulletin.vlan, VLAN_HLEN);

	/* copy new bulletin board to bp */
	bp->old_bulletin = bulletin;

	return PFVF_BULLETIN_UPDATED;
}