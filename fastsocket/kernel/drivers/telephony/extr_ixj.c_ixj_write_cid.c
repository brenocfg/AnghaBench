#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_16__   TYPE_4__ ;
typedef  struct TYPE_15__   TYPE_3__ ;
typedef  struct TYPE_14__   TYPE_2__ ;
typedef  struct TYPE_13__   TYPE_1__ ;

/* Type definitions */
struct TYPE_15__ {int /*<<< orphan*/  name; int /*<<< orphan*/  number; int /*<<< orphan*/  min; int /*<<< orphan*/  hour; int /*<<< orphan*/  day; int /*<<< orphan*/  month; } ;
struct TYPE_14__ {scalar_t__ cidplay; } ;
struct TYPE_13__ {int low; } ;
struct TYPE_16__ {int fskz; int fskphase; int fskcnt; int fskdcnt; TYPE_3__ cid_send; scalar_t__ cidcnt; scalar_t__ cidsize; TYPE_2__ flags; TYPE_1__ dsp; } ;
typedef  TYPE_4__ IXJ ;

/* Variables and functions */
 int /*<<< orphan*/  ixj_fsk_alloc (TYPE_4__*) ; 
 int ixj_hookstate (TYPE_4__*) ; 
 int /*<<< orphan*/  ixj_pad_fsk (TYPE_4__*,int) ; 
 int /*<<< orphan*/  ixj_write_cid_byte (TYPE_4__*,char) ; 
 int /*<<< orphan*/  ixj_write_cid_seize (TYPE_4__*) ; 
 int ixj_write_cid_string (TYPE_4__*,char*,int) ; 
 int /*<<< orphan*/  ixj_write_frame (TYPE_4__*) ; 
 int /*<<< orphan*/  strcat (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strcpy (char*,int /*<<< orphan*/ ) ; 
 char strlen (char*) ; 

__attribute__((used)) static void ixj_write_cid(IXJ *j)
{
	char sdmf1[50];
	char sdmf2[50];
	char sdmf3[80];
	char mdmflen, len1, len2, len3;
	int pad;

	int checksum = 0;

	if (j->dsp.low == 0x20 || j->flags.cidplay)
		return;

	j->fskz = j->fskphase = j->fskcnt = j->fskdcnt = 0;
	j->cidsize = j->cidcnt = 0;

	ixj_fsk_alloc(j);

	strcpy(sdmf1, j->cid_send.month);
	strcat(sdmf1, j->cid_send.day);
	strcat(sdmf1, j->cid_send.hour);
	strcat(sdmf1, j->cid_send.min);
	strcpy(sdmf2, j->cid_send.number);
	strcpy(sdmf3, j->cid_send.name);

	len1 = strlen(sdmf1);
	len2 = strlen(sdmf2);
	len3 = strlen(sdmf3);
	mdmflen = len1 + len2 + len3 + 6;

	while(1){
		ixj_write_cid_seize(j);

		ixj_write_cid_byte(j, 0x80);
		checksum = 0x80;
		ixj_write_cid_byte(j, mdmflen);
		checksum = checksum + mdmflen;

		ixj_write_cid_byte(j, 0x01);
		checksum = checksum + 0x01;
		ixj_write_cid_byte(j, len1);
		checksum = checksum + len1;
		checksum = ixj_write_cid_string(j, sdmf1, checksum);
		if(ixj_hookstate(j) & 1)
			break;

		ixj_write_cid_byte(j, 0x02);
		checksum = checksum + 0x02;
		ixj_write_cid_byte(j, len2);
		checksum = checksum + len2;
		checksum = ixj_write_cid_string(j, sdmf2, checksum);
		if(ixj_hookstate(j) & 1)
			break;

		ixj_write_cid_byte(j, 0x07);
		checksum = checksum + 0x07;
		ixj_write_cid_byte(j, len3);
		checksum = checksum + len3;
		checksum = ixj_write_cid_string(j, sdmf3, checksum);
		if(ixj_hookstate(j) & 1)
			break;

		checksum %= 256;
		checksum ^= 0xFF;
		checksum += 1;

		ixj_write_cid_byte(j, (char) checksum);

		pad = j->fskdcnt % 240;
		if (pad) {
			pad = 240 - pad;
		}
		ixj_pad_fsk(j, pad);
		break;
	}

	ixj_write_frame(j);
}