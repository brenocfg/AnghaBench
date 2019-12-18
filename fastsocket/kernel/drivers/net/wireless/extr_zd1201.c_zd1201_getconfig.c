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
struct zd1201 {int rxlen; unsigned char* rxdata; TYPE_1__* usb; scalar_t__ rxdatas; int /*<<< orphan*/  rxdataq; } ;
typedef  int /*<<< orphan*/  __le16 ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int EINVAL ; 
 int EIO ; 
 int ENODATA ; 
 int ZD1201_ACCESSBIT ; 
 int /*<<< orphan*/  ZD1201_CMDCODE_ACCESS ; 
 int /*<<< orphan*/  ZD1201_CMDCODE_SETRXRID ; 
 unsigned char ZD1201_PACKET_RESOURCE ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*,unsigned char,...) ; 
 int le16_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (void*,unsigned char*,int) ; 
 int /*<<< orphan*/  wait_event_interruptible (int /*<<< orphan*/ ,scalar_t__) ; 
 int zd1201_docmd (struct zd1201*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int zd1201_getconfig(struct zd1201 *zd, int rid, void *riddata,
	unsigned int riddatalen)
{
	int err;
	int i = 0;
	int code;
	int rid_fid;
	int length;
	unsigned char *pdata;

	zd->rxdatas = 0;
	err = zd1201_docmd(zd, ZD1201_CMDCODE_ACCESS, rid, 0, 0);
	if (err)
		return err;

	wait_event_interruptible(zd->rxdataq, zd->rxdatas);
	if (!zd->rxlen)
		return -EIO;

	code = le16_to_cpu(*(__le16*)(&zd->rxdata[4]));
	rid_fid = le16_to_cpu(*(__le16*)(&zd->rxdata[6]));
	length = le16_to_cpu(*(__le16*)(&zd->rxdata[8]));
	if (length > zd->rxlen)
		length = zd->rxlen-6;

	/* If access bit is not on, then error */
	if ((code & ZD1201_ACCESSBIT) != ZD1201_ACCESSBIT || rid_fid != rid )
		return -EINVAL;

	/* Not enough buffer for allocating data */
	if (riddatalen != (length - 4)) {
		dev_dbg(&zd->usb->dev, "riddatalen mismatches, expected=%u, (packet=%u) length=%u, rid=0x%04X, rid_fid=0x%04X\n",
		    riddatalen, zd->rxlen, length, rid, rid_fid);
		return -ENODATA;
	}

	zd->rxdatas = 0;
	/* Issue SetRxRid commnd */			
	err = zd1201_docmd(zd, ZD1201_CMDCODE_SETRXRID, rid, 0, length);
	if (err)
		return err;

	/* Receive RID record from resource packets */
	wait_event_interruptible(zd->rxdataq, zd->rxdatas);
	if (!zd->rxlen)
		return -EIO;

	if (zd->rxdata[zd->rxlen - 1] != ZD1201_PACKET_RESOURCE) {
		dev_dbg(&zd->usb->dev, "Packet type mismatch: 0x%x not 0x3\n",
		    zd->rxdata[zd->rxlen-1]);
		return -EINVAL;
	}

	/* Set the data pointer and received data length */
	pdata = zd->rxdata;
	length = zd->rxlen;

	do {
		int actual_length;

		actual_length = (length > 64) ? 64 : length;

		if (pdata[0] != 0x3) {
			dev_dbg(&zd->usb->dev, "Rx Resource packet type error: %02X\n",
			    pdata[0]);
			return -EINVAL;
		}

		if (actual_length != 64) {
			/* Trim the last packet type byte */
			actual_length--;
		}

		/* Skip the 4 bytes header (RID length and RID) */
		if (i == 0) {
			pdata += 8;
			actual_length -= 8;
		} else {
			pdata += 4;
			actual_length -= 4;
		}
		
		memcpy(riddata, pdata, actual_length);
		riddata += actual_length;
		pdata += actual_length;
		length -= 64;
		i++;
	} while (length > 0);

	return 0;
}