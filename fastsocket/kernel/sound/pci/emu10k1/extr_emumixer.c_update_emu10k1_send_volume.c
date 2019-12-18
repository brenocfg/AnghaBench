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
struct snd_emu10k1 {scalar_t__ audigy; } ;

/* Variables and functions */
 int /*<<< orphan*/  A_SENDAMOUNTS ; 
 int /*<<< orphan*/  DSL_FXSENDAMOUNT_D ; 
 int /*<<< orphan*/  PSST_FXSENDAMOUNT_C ; 
 int /*<<< orphan*/  PTRX_FXSENDAMOUNT_A ; 
 int /*<<< orphan*/  PTRX_FXSENDAMOUNT_B ; 
 int /*<<< orphan*/  snd_emu10k1_ptr_write (struct snd_emu10k1*,int /*<<< orphan*/ ,int,unsigned int) ; 

__attribute__((used)) static void update_emu10k1_send_volume(struct snd_emu10k1 *emu, int voice, unsigned char *volume)
{
	snd_emu10k1_ptr_write(emu, PTRX_FXSENDAMOUNT_A, voice, volume[0]);
	snd_emu10k1_ptr_write(emu, PTRX_FXSENDAMOUNT_B, voice, volume[1]);
	snd_emu10k1_ptr_write(emu, PSST_FXSENDAMOUNT_C, voice, volume[2]);
	snd_emu10k1_ptr_write(emu, DSL_FXSENDAMOUNT_D, voice, volume[3]);
	if (emu->audigy) {
		unsigned int val = ((unsigned int)volume[4] << 24) |
			((unsigned int)volume[5] << 16) |
			((unsigned int)volume[6] << 8) |
			(unsigned int)volume[7];
		snd_emu10k1_ptr_write(emu, A_SENDAMOUNTS, voice, val);
	}
}