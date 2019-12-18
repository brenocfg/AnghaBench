#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_17__   TYPE_6__ ;
typedef  struct TYPE_16__   TYPE_5__ ;
typedef  struct TYPE_15__   TYPE_4__ ;
typedef  struct TYPE_14__   TYPE_3__ ;
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
struct TYPE_17__ {char numlen; char namelen; int /*<<< orphan*/  name; int /*<<< orphan*/  number; int /*<<< orphan*/  min; int /*<<< orphan*/  hour; int /*<<< orphan*/  day; int /*<<< orphan*/  month; } ;
struct TYPE_16__ {int high; int low; } ;
struct TYPE_12__ {char* CallerID; } ;
struct TYPE_13__ {TYPE_1__ CAO; } ;
struct TYPE_14__ {TYPE_2__ CAO_REGS; } ;
struct TYPE_15__ {TYPE_6__ cid; TYPE_3__ m_DAAShadowRegs; scalar_t__ XILINXbase; } ;
typedef  int /*<<< orphan*/  PHONE_CID ;
typedef  TYPE_4__ IXJ ;
typedef  TYPE_5__ BYTES ;

/* Variables and functions */
 int ALISDAA_CALLERID_SIZE ; 
 int ALISDAA_ID_BYTE ; 
 int /*<<< orphan*/  SCI_Control (TYPE_4__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SCI_Enable_DAA ; 
 int /*<<< orphan*/  SCI_End ; 
 int /*<<< orphan*/  SCI_Prepare (TYPE_4__*) ; 
 int /*<<< orphan*/  SCI_WaitHighSCI (TYPE_4__*) ; 
 void* inb_p (scalar_t__) ; 
 int /*<<< orphan*/  ixj_daa_cid_reset (TYPE_4__*) ; 
 int ixjdebug ; 
 int /*<<< orphan*/  memset (TYPE_6__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  outb_p (int,scalar_t__) ; 
 int /*<<< orphan*/  printk (char*,int,int) ; 
 int /*<<< orphan*/  strncpy (int /*<<< orphan*/ ,char*,int) ; 

__attribute__((used)) static int ixj_daa_cid_read(IXJ *j)
{
	int i;
	BYTES bytes;
	char CID[ALISDAA_CALLERID_SIZE];
	bool mContinue;
	char *pIn, *pOut;

	if (!SCI_Prepare(j))
		return 0;

	bytes.high = 0x78;
	bytes.low = 0x00;
	outb_p(bytes.high, j->XILINXbase + 0x03);
	outb_p(bytes.low, j->XILINXbase + 0x02);

	if (!SCI_Control(j, SCI_Enable_DAA))
		return 0;

	if (!SCI_WaitHighSCI(j))
		return 0;

	bytes.high = inb_p(j->XILINXbase + 0x03);
	bytes.low = inb_p(j->XILINXbase + 0x02);
	if (bytes.low != ALISDAA_ID_BYTE) {
		if (ixjdebug & 0x0001)
			printk("DAA Get Version Cannot read DAA ID Byte high = %d low = %d\n", bytes.high, bytes.low);
		return 0;
	}
	for (i = 0; i < ALISDAA_CALLERID_SIZE; i += 2) {
		bytes.high = bytes.low = 0x00;
		outb_p(bytes.high, j->XILINXbase + 0x03);
		outb_p(bytes.low, j->XILINXbase + 0x02);

		if (!SCI_Control(j, SCI_Enable_DAA))
			return 0;

		if (!SCI_WaitHighSCI(j))
			return 0;

		CID[i + 0] = inb_p(j->XILINXbase + 0x03);
		CID[i + 1] = inb_p(j->XILINXbase + 0x02);
	}

	if (!SCI_Control(j, SCI_End))
		return 0;

	pIn = CID;
	pOut = j->m_DAAShadowRegs.CAO_REGS.CAO.CallerID;
	mContinue = true;
	while (mContinue) {
		if ((pIn[1] & 0x03) == 0x01) {
			pOut[0] = pIn[0];
		}
		if ((pIn[2] & 0x0c) == 0x04) {
			pOut[1] = ((pIn[2] & 0x03) << 6) | ((pIn[1] & 0xfc) >> 2);
		}
		if ((pIn[3] & 0x30) == 0x10) {
			pOut[2] = ((pIn[3] & 0x0f) << 4) | ((pIn[2] & 0xf0) >> 4);
		}
		if ((pIn[4] & 0xc0) == 0x40) {
			pOut[3] = ((pIn[4] & 0x3f) << 2) | ((pIn[3] & 0xc0) >> 6);
		} else {
			mContinue = false;
		}
		pIn += 5, pOut += 4;
	}
	memset(&j->cid, 0, sizeof(PHONE_CID));
	pOut = j->m_DAAShadowRegs.CAO_REGS.CAO.CallerID;
	pOut += 4;
	strncpy(j->cid.month, pOut, 2);
	pOut += 2;
	strncpy(j->cid.day, pOut, 2);
	pOut += 2;
	strncpy(j->cid.hour, pOut, 2);
	pOut += 2;
	strncpy(j->cid.min, pOut, 2);
	pOut += 3;
	j->cid.numlen = *pOut;
	pOut += 1;
	strncpy(j->cid.number, pOut, j->cid.numlen);
	pOut += j->cid.numlen + 1;
	j->cid.namelen = *pOut;
	pOut += 1;
	strncpy(j->cid.name, pOut, j->cid.namelen);

	ixj_daa_cid_reset(j);
	return 1;
}