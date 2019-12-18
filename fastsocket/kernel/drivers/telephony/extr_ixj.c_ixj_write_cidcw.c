#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_23__   TYPE_5__ ;
typedef  struct TYPE_22__   TYPE_4__ ;
typedef  struct TYPE_21__   TYPE_3__ ;
typedef  struct TYPE_20__   TYPE_2__ ;
typedef  struct TYPE_19__   TYPE_1__ ;

/* Type definitions */
struct TYPE_21__ {int /*<<< orphan*/  name; int /*<<< orphan*/  number; int /*<<< orphan*/  min; int /*<<< orphan*/  hour; int /*<<< orphan*/  day; int /*<<< orphan*/  month; } ;
struct TYPE_20__ {scalar_t__ cidcw_ack; scalar_t__ cidplay; } ;
struct TYPE_19__ {int low; } ;
struct TYPE_23__ {int fskz; int fskphase; int fskcnt; int fskdcnt; int /*<<< orphan*/  board; TYPE_3__ cid_send; TYPE_2__ flags; int /*<<< orphan*/  write_q; scalar_t__ cid_play_flag; scalar_t__ cidcw_wait; int /*<<< orphan*/  busyflags; scalar_t__ tone_state; scalar_t__ cidcnt; scalar_t__ cidsize; TYPE_1__ dsp; } ;
struct TYPE_22__ {int tone_index; int gain0; scalar_t__ freq1; scalar_t__ gain1; int /*<<< orphan*/  freq0; } ;
typedef  TYPE_4__ IXJ_TONE ;
typedef  TYPE_5__ IXJ ;

/* Variables and functions */
 int /*<<< orphan*/  clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int hertz ; 
 int /*<<< orphan*/  hz2130 ; 
 scalar_t__ hz2750 ; 
 int /*<<< orphan*/  hz440 ; 
 int /*<<< orphan*/  ixj_fsk_alloc (TYPE_5__*) ; 
 int /*<<< orphan*/  ixj_init_tone (TYPE_5__*,TYPE_4__*) ; 
 int /*<<< orphan*/  ixj_pad_fsk (TYPE_5__*,int) ; 
 int /*<<< orphan*/  ixj_play_tone (TYPE_5__*,int) ; 
 int /*<<< orphan*/  ixj_post_cid (TYPE_5__*) ; 
 int /*<<< orphan*/  ixj_pre_cid (TYPE_5__*) ; 
 int /*<<< orphan*/  ixj_set_tone_off (int,TYPE_5__*) ; 
 int /*<<< orphan*/  ixj_set_tone_on (int,TYPE_5__*) ; 
 int /*<<< orphan*/  ixj_write_cid_byte (TYPE_5__*,char) ; 
 int ixj_write_cid_string (TYPE_5__*,char*,int) ; 
 int /*<<< orphan*/  ixj_write_cidcw_seize (TYPE_5__*) ; 
 int ixjdebug ; 
 scalar_t__ jiffies ; 
 int /*<<< orphan*/  printk (char*,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  schedule_timeout_interruptible (int) ; 
 int /*<<< orphan*/  strcat (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strcpy (char*,int /*<<< orphan*/ ) ; 
 char strlen (char*) ; 
 scalar_t__ test_and_set_bit (int /*<<< orphan*/ ,void*) ; 
 scalar_t__ time_before (scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  wake_up_interruptible (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void ixj_write_cidcw(IXJ *j)
{
	IXJ_TONE ti;

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

	j->flags.cidcw_ack = 0;

	ti.tone_index = 23;
	ti.gain0 = 1;
	ti.freq0 = hz440;
	ti.gain1 = 0;
	ti.freq1 = 0;
	ixj_init_tone(j, &ti);

	ixj_set_tone_on(1500, j);
	ixj_set_tone_off(32, j);
	if(ixjdebug & 0x0200) {
		printk("IXJ cidcw phone%d first tone start at %ld\n", j->board, jiffies);
	}
	ixj_play_tone(j, 23);

	clear_bit(j->board, &j->busyflags);
	while(j->tone_state)
		schedule_timeout_interruptible(1);
	while(test_and_set_bit(j->board, (void *)&j->busyflags) != 0)
		schedule_timeout_interruptible(1);
	if(ixjdebug & 0x0200) {
		printk("IXJ cidcw phone%d first tone end at %ld\n", j->board, jiffies);
	}

	ti.tone_index = 24;
	ti.gain0 = 1;
	ti.freq0 = hz2130;
	ti.gain1 = 0;
	ti.freq1 = hz2750;
	ixj_init_tone(j, &ti);

	ixj_set_tone_off(10, j);
	ixj_set_tone_on(600, j);
	if(ixjdebug & 0x0200) {
		printk("IXJ cidcw phone%d second tone start at %ld\n", j->board, jiffies);
	}
	ixj_play_tone(j, 24);

	clear_bit(j->board, &j->busyflags);
	while(j->tone_state)
		schedule_timeout_interruptible(1);
	while(test_and_set_bit(j->board, (void *)&j->busyflags) != 0)
		schedule_timeout_interruptible(1);
	if(ixjdebug & 0x0200) {
		printk("IXJ cidcw phone%d sent second tone at %ld\n", j->board, jiffies);
	}

	j->cidcw_wait = jiffies + ((50 * hertz) / 100);

	clear_bit(j->board, &j->busyflags);
	while(!j->flags.cidcw_ack && time_before(jiffies, j->cidcw_wait))
		schedule_timeout_interruptible(1);
	while(test_and_set_bit(j->board, (void *)&j->busyflags) != 0)
		schedule_timeout_interruptible(1);
	j->cidcw_wait = 0;
	if(!j->flags.cidcw_ack) {
		if(ixjdebug & 0x0200) {
			printk("IXJ cidcw phone%d did not receive ACK from display %ld\n", j->board, jiffies);
		}
		ixj_post_cid(j);
		if(j->cid_play_flag) {
			wake_up_interruptible(&j->write_q);	/* Wake any blocked readers */
		}
		return;
	} else {
		ixj_pre_cid(j);
	}
	j->flags.cidcw_ack = 0;
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

	ixj_write_cidcw_seize(j);

	ixj_write_cid_byte(j, 0x80);
	checksum = 0x80;
	ixj_write_cid_byte(j, mdmflen);
	checksum = checksum + mdmflen;

	ixj_write_cid_byte(j, 0x01);
	checksum = checksum + 0x01;
	ixj_write_cid_byte(j, len1);
	checksum = checksum + len1;
	checksum = ixj_write_cid_string(j, sdmf1, checksum);

	ixj_write_cid_byte(j, 0x02);
	checksum = checksum + 0x02;
	ixj_write_cid_byte(j, len2);
	checksum = checksum + len2;
	checksum = ixj_write_cid_string(j, sdmf2, checksum);

	ixj_write_cid_byte(j, 0x07);
	checksum = checksum + 0x07;
	ixj_write_cid_byte(j, len3);
	checksum = checksum + len3;
	checksum = ixj_write_cid_string(j, sdmf3, checksum);

	checksum %= 256;
	checksum ^= 0xFF;
	checksum += 1;

	ixj_write_cid_byte(j, (char) checksum);

	pad = j->fskdcnt % 240;
	if (pad) {
		pad = 240 - pad;
	}
	ixj_pad_fsk(j, pad);
	if(ixjdebug & 0x0200) {
		printk("IXJ cidcw phone%d sent FSK data at %ld\n", j->board, jiffies);
	}
}