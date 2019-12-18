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
struct TYPE_10__ {int z1; int z2; } ;
typedef  TYPE_4__ z_type ;
typedef  size_t u_char ;
struct TYPE_8__ {scalar_t__ fifos; } ;
struct TYPE_9__ {TYPE_2__ hfcpci; } ;
struct IsdnCardState {int debug; size_t* dlog; int /*<<< orphan*/  HW_Flags; TYPE_3__ hw; } ;
struct TYPE_12__ {int f1; int f2; TYPE_4__* za; } ;
struct TYPE_7__ {size_t* rxdat_b2; TYPE_6__ rxbz_b2; } ;
struct TYPE_11__ {TYPE_1__ b_chans; } ;
typedef  TYPE_5__ fifo_area ;
typedef  TYPE_6__ bzfifo_type ;

/* Variables and functions */
 int B_FIFO_SIZE ; 
 int B_SUB_VAL ; 
 int DEB_DLOG_HEX ; 
 int /*<<< orphan*/  FLG_LOCK_ATOMIC ; 
 int /*<<< orphan*/  HiSax_putstatus (struct IsdnCardState*,char*,...) ; 
 int L1_DEB_ISAC ; 
 int L1_DEB_WARN ; 
 int MAX_B_FRAMES ; 
 int MAX_DLOG_SPACE ; 
 int /*<<< orphan*/  QuickHex (size_t*,size_t*,int) ; 
 int /*<<< orphan*/  debugl1 (struct IsdnCardState*,char*,...) ; 
 int /*<<< orphan*/  memcpy (size_t*,size_t*,int) ; 
 int /*<<< orphan*/  test_and_clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ test_and_set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
receive_emsg(struct IsdnCardState *cs)
{
	int rcnt;
	int receive, count = 5;
	bzfifo_type *bz;
	u_char *bdata;
	z_type *zp;
	u_char *ptr, *ptr1, new_f2;
	int total, maxlen, new_z2;
	u_char e_buffer[256];

	bz = &((fifo_area *) (cs->hw.hfcpci.fifos))->b_chans.rxbz_b2;
	bdata = ((fifo_area *) (cs->hw.hfcpci.fifos))->b_chans.rxdat_b2;
      Begin:
	count--;
	if (test_and_set_bit(FLG_LOCK_ATOMIC, &cs->HW_Flags)) {
		debugl1(cs, "echo_rec_data blocked");
		return;
	}
	if (bz->f1 != bz->f2) {
		if (cs->debug & L1_DEB_ISAC)
			debugl1(cs, "hfcpci e_rec f1(%d) f2(%d)",
				bz->f1, bz->f2);
		zp = &bz->za[bz->f2];

		rcnt = zp->z1 - zp->z2;
		if (rcnt < 0)
			rcnt += B_FIFO_SIZE;
		rcnt++;
		if (cs->debug & L1_DEB_ISAC)
			debugl1(cs, "hfcpci e_rec z1(%x) z2(%x) cnt(%d)",
				zp->z1, zp->z2, rcnt);
		new_z2 = zp->z2 + rcnt;		/* new position in fifo */
		if (new_z2 >= (B_FIFO_SIZE + B_SUB_VAL))
			new_z2 -= B_FIFO_SIZE;	/* buffer wrap */
		new_f2 = (bz->f2 + 1) & MAX_B_FRAMES;
		if ((rcnt > 256 + 3) || (count < 4) ||
		    (*(bdata + (zp->z1 - B_SUB_VAL)))) {
			if (cs->debug & L1_DEB_WARN)
				debugl1(cs, "hfcpci_empty_echan: incoming packet invalid length %d or crc", rcnt);
			bz->za[new_f2].z2 = new_z2;
			bz->f2 = new_f2;	/* next buffer */
		} else {
			total = rcnt;
			rcnt -= 3;
			ptr = e_buffer;

			if (zp->z2 <= B_FIFO_SIZE + B_SUB_VAL)
				maxlen = rcnt;	/* complete transfer */
			else
				maxlen = B_FIFO_SIZE + B_SUB_VAL - zp->z2;	/* maximum */

			ptr1 = bdata + (zp->z2 - B_SUB_VAL);	/* start of data */
			memcpy(ptr, ptr1, maxlen);	/* copy data */
			rcnt -= maxlen;

			if (rcnt) {	/* rest remaining */
				ptr += maxlen;
				ptr1 = bdata;	/* start of buffer */
				memcpy(ptr, ptr1, rcnt);	/* rest */
			}
			bz->za[new_f2].z2 = new_z2;
			bz->f2 = new_f2;	/* next buffer */
			if (cs->debug & DEB_DLOG_HEX) {
				ptr = cs->dlog;
				if ((total - 3) < MAX_DLOG_SPACE / 3 - 10) {
					*ptr++ = 'E';
					*ptr++ = 'C';
					*ptr++ = 'H';
					*ptr++ = 'O';
					*ptr++ = ':';
					ptr += QuickHex(ptr, e_buffer, total - 3);
					ptr--;
					*ptr++ = '\n';
					*ptr = 0;
					HiSax_putstatus(cs, NULL, cs->dlog);
				} else
					HiSax_putstatus(cs, "LogEcho: ", "warning Frame too big (%d)", total - 3);
			}
		}

		rcnt = bz->f1 - bz->f2;
		if (rcnt < 0)
			rcnt += MAX_B_FRAMES + 1;
		if (rcnt > 1)
			receive = 1;
		else
			receive = 0;
	} else
		receive = 0;
	test_and_clear_bit(FLG_LOCK_ATOMIC, &cs->HW_Flags);
	if (count && receive)
		goto Begin;
}