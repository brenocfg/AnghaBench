#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int u16 ;
struct TYPE_9__ {scalar_t__ enabled; } ;
struct airo_info {TYPE_2__ micstats; int /*<<< orphan*/  flags; TYPE_1__* dev; } ;
typedef  int /*<<< orphan*/  payloadLen ;
typedef  int /*<<< orphan*/  pMic ;
typedef  int /*<<< orphan*/  etherHead ;
typedef  int /*<<< orphan*/  cmd ;
typedef  int /*<<< orphan*/  __le16 ;
typedef  int /*<<< orphan*/  __be16 ;
struct TYPE_11__ {int parm0; int /*<<< orphan*/  cmd; } ;
struct TYPE_10__ {int status; } ;
struct TYPE_8__ {int /*<<< orphan*/  name; } ;
typedef  TYPE_3__ Resp ;
typedef  int /*<<< orphan*/  MICBuffer ;
typedef  TYPE_4__ Cmd ;

/* Variables and functions */
 int /*<<< orphan*/  BAP1 ; 
 int /*<<< orphan*/  CMD_TRANSMIT ; 
 int ERROR ; 
 int ETH_ALEN ; 
 int /*<<< orphan*/  FLAG_MIC_CAPABLE ; 
 scalar_t__ SUCCESS ; 
 int /*<<< orphan*/  airo_print_warn (int /*<<< orphan*/ ,char*,int) ; 
 scalar_t__ bap_setup (struct airo_info*,int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bap_write (struct airo_info*,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cpu_to_le16 (int) ; 
 scalar_t__ encapsulate (struct airo_info*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 scalar_t__ issuecommand (struct airo_info*,TYPE_4__*,TYPE_3__*) ; 
 int /*<<< orphan*/  memset (TYPE_4__*,int /*<<< orphan*/ ,int) ; 
 int ntohs (int /*<<< orphan*/ ) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int transmit_802_3_packet(struct airo_info *ai, int len, char *pPacket)
{
	__le16 payloadLen;
	Cmd cmd;
	Resp rsp;
	int miclen = 0;
	u16 txFid = len;
	MICBuffer pMic;

	len >>= 16;

	if (len <= ETH_ALEN * 2) {
		airo_print_warn(ai->dev->name, "Short packet %d", len);
		return ERROR;
	}
	len -= ETH_ALEN * 2;

	if (test_bit(FLAG_MIC_CAPABLE, &ai->flags) && ai->micstats.enabled && 
	    (ntohs(((__be16 *)pPacket)[6]) != 0x888E)) {
		if (encapsulate(ai,(etherHead *)pPacket,&pMic,len) != SUCCESS)
			return ERROR;
		miclen = sizeof(pMic);
	}
	// packet is destination[6], source[6], payload[len-12]
	// write the payload length and dst/src/payload
	if (bap_setup(ai, txFid, 0x0036, BAP1) != SUCCESS) return ERROR;
	/* The hardware addresses aren't counted as part of the payload, so
	 * we have to subtract the 12 bytes for the addresses off */
	payloadLen = cpu_to_le16(len + miclen);
	bap_write(ai, &payloadLen, sizeof(payloadLen),BAP1);
	bap_write(ai, (__le16*)pPacket, sizeof(etherHead), BAP1);
	if (miclen)
		bap_write(ai, (__le16*)&pMic, miclen, BAP1);
	bap_write(ai, (__le16*)(pPacket + sizeof(etherHead)), len, BAP1);
	// issue the transmit command
	memset( &cmd, 0, sizeof( cmd ) );
	cmd.cmd = CMD_TRANSMIT;
	cmd.parm0 = txFid;
	if (issuecommand(ai, &cmd, &rsp) != SUCCESS) return ERROR;
	if ( (rsp.status & 0xFF00) != 0) return ERROR;
	return SUCCESS;
}