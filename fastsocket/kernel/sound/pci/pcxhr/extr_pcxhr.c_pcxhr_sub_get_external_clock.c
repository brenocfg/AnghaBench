#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct pcxhr_rmh {int cmd_len; unsigned char* cmd; int* stat; } ;
struct pcxhr_mgr {unsigned char last_reg_stat; } ;
typedef  enum pcxhr_clock_type { ____Placeholder_pcxhr_clock_type } pcxhr_clock_type ;

/* Variables and functions */
 int /*<<< orphan*/  CMD_ACCESS_IO_READ ; 
 int EINVAL ; 
 unsigned char IO_NUM_REG_STATUS ; 
#define  PCXHR_CLOCK_TYPE_AES_1 142 
#define  PCXHR_CLOCK_TYPE_AES_2 141 
#define  PCXHR_CLOCK_TYPE_AES_3 140 
#define  PCXHR_CLOCK_TYPE_AES_4 139 
#define  PCXHR_CLOCK_TYPE_AES_SYNC 138 
#define  PCXHR_CLOCK_TYPE_WORD_CLOCK 137 
 unsigned char REG_STATUS_AES_1 ; 
 unsigned char REG_STATUS_AES_2 ; 
 unsigned char REG_STATUS_AES_3 ; 
 unsigned char REG_STATUS_AES_4 ; 
 unsigned char REG_STATUS_AES_SYNC ; 
 unsigned char REG_STATUS_CURRENT ; 
#define  REG_STATUS_SYNC_128000 136 
#define  REG_STATUS_SYNC_176400 135 
#define  REG_STATUS_SYNC_192000 134 
#define  REG_STATUS_SYNC_32000 133 
#define  REG_STATUS_SYNC_44100 132 
#define  REG_STATUS_SYNC_48000 131 
#define  REG_STATUS_SYNC_64000 130 
#define  REG_STATUS_SYNC_88200 129 
#define  REG_STATUS_SYNC_96000 128 
 unsigned char REG_STATUS_WORD_CLOCK ; 
 int /*<<< orphan*/  pcxhr_init_rmh (struct pcxhr_rmh*,int /*<<< orphan*/ ) ; 
 int pcxhr_send_msg (struct pcxhr_mgr*,struct pcxhr_rmh*) ; 
 int /*<<< orphan*/  snd_printdd (char*,int) ; 
 int /*<<< orphan*/  udelay (int) ; 

__attribute__((used)) static int pcxhr_sub_get_external_clock(struct pcxhr_mgr *mgr,
					enum pcxhr_clock_type clock_type,
					int *sample_rate)
{
	struct pcxhr_rmh rmh;
	unsigned char reg;
	int err, rate;

	switch (clock_type) {
	case PCXHR_CLOCK_TYPE_WORD_CLOCK:
		reg = REG_STATUS_WORD_CLOCK;
		break;
	case PCXHR_CLOCK_TYPE_AES_SYNC:
		reg = REG_STATUS_AES_SYNC;
		break;
	case PCXHR_CLOCK_TYPE_AES_1:
		reg = REG_STATUS_AES_1;
		break;
	case PCXHR_CLOCK_TYPE_AES_2:
		reg = REG_STATUS_AES_2;
		break;
	case PCXHR_CLOCK_TYPE_AES_3:
		reg = REG_STATUS_AES_3;
		break;
	case PCXHR_CLOCK_TYPE_AES_4:
		reg = REG_STATUS_AES_4;
		break;
	default:
		return -EINVAL;
	}
	pcxhr_init_rmh(&rmh, CMD_ACCESS_IO_READ);
	rmh.cmd_len = 2;
	rmh.cmd[0] |= IO_NUM_REG_STATUS;
	if (mgr->last_reg_stat != reg) {
		rmh.cmd[1]  = reg;
		err = pcxhr_send_msg(mgr, &rmh);
		if (err)
			return err;
		udelay(100);	/* wait minimum 2 sample_frames at 32kHz ! */
		mgr->last_reg_stat = reg;
	}
	rmh.cmd[1]  = REG_STATUS_CURRENT;
	err = pcxhr_send_msg(mgr, &rmh);
	if (err)
		return err;
	switch (rmh.stat[1] & 0x0f) {
	case REG_STATUS_SYNC_32000 :	rate = 32000; break;
	case REG_STATUS_SYNC_44100 :	rate = 44100; break;
	case REG_STATUS_SYNC_48000 :	rate = 48000; break;
	case REG_STATUS_SYNC_64000 :	rate = 64000; break;
	case REG_STATUS_SYNC_88200 :	rate = 88200; break;
	case REG_STATUS_SYNC_96000 :	rate = 96000; break;
	case REG_STATUS_SYNC_128000 :	rate = 128000; break;
	case REG_STATUS_SYNC_176400 :	rate = 176400; break;
	case REG_STATUS_SYNC_192000 :	rate = 192000; break;
	default: rate = 0;
	}
	snd_printdd("External clock is at %d Hz\n", rate);
	*sample_rate = rate;
	return 0;
}