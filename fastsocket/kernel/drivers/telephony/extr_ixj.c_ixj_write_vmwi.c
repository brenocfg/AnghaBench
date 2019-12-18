#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct TYPE_11__ {scalar_t__ cidplay; } ;
struct TYPE_10__ {int low; } ;
struct TYPE_12__ {int fskz; int fskphase; int fskcnt; int fskdcnt; scalar_t__ port; scalar_t__ cidcnt; scalar_t__ cidsize; TYPE_2__ flags; TYPE_1__ dsp; } ;
typedef  TYPE_3__ IXJ ;

/* Variables and functions */
 int /*<<< orphan*/  PLD_SLIC_STATE_OHT ; 
 scalar_t__ PORT_POTS ; 
 int /*<<< orphan*/  SLIC_SetState (int /*<<< orphan*/ ,TYPE_3__*) ; 
 int /*<<< orphan*/  ixj_fsk_alloc (TYPE_3__*) ; 
 int /*<<< orphan*/  ixj_pad_fsk (TYPE_3__*,int) ; 
 int /*<<< orphan*/  ixj_write_cid_byte (TYPE_3__*,char) ; 
 int /*<<< orphan*/  ixj_write_cid_seize (TYPE_3__*) ; 

__attribute__((used)) static void ixj_write_vmwi(IXJ *j, int msg)
{
	char mdmflen;
	int pad;

	int checksum = 0;

	if (j->dsp.low == 0x20 || j->flags.cidplay)
		return;

	j->fskz = j->fskphase = j->fskcnt = j->fskdcnt = 0;
	j->cidsize = j->cidcnt = 0;

	ixj_fsk_alloc(j);

	mdmflen = 3;

	if (j->port == PORT_POTS)
		SLIC_SetState(PLD_SLIC_STATE_OHT, j);

	ixj_write_cid_seize(j);

	ixj_write_cid_byte(j, 0x82);
	checksum = 0x82;
	ixj_write_cid_byte(j, mdmflen);
	checksum = checksum + mdmflen;

	ixj_write_cid_byte(j, 0x0B);
	checksum = checksum + 0x0B;
	ixj_write_cid_byte(j, 1);
	checksum = checksum + 1;

	if(msg) {
		ixj_write_cid_byte(j, 0xFF);
		checksum = checksum + 0xFF;
	}
	else {
		ixj_write_cid_byte(j, 0x00);
		checksum = checksum + 0x00;
	}

	checksum %= 256;
	checksum ^= 0xFF;
	checksum += 1;

	ixj_write_cid_byte(j, (char) checksum);

	pad = j->fskdcnt % 240;
	if (pad) {
		pad = 240 - pad;
	}
	ixj_pad_fsk(j, pad);
}