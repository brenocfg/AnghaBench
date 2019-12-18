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
struct snd_emu10k1 {scalar_t__ port; scalar_t__ audigy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ADCBA ; 
 int /*<<< orphan*/  ADCBS ; 
 int /*<<< orphan*/  ADCBS_BUFSIZE_NONE ; 
 int /*<<< orphan*/  A_DBG ; 
 int /*<<< orphan*/  A_DBG_SINGLE_STEP ; 
 int /*<<< orphan*/  CLIEH ; 
 int /*<<< orphan*/  CLIEL ; 
 int /*<<< orphan*/  CPF ; 
 int /*<<< orphan*/  CVCF ; 
 int /*<<< orphan*/  DBG ; 
 int /*<<< orphan*/  DCYSUSV ; 
 int /*<<< orphan*/  EMU10K1_DBG_SINGLE_STEP ; 
 int /*<<< orphan*/  FXBA ; 
 int /*<<< orphan*/  FXBS ; 
 int /*<<< orphan*/  FXWC ; 
 scalar_t__ HCFG ; 
 int HCFG_LOCKSOUNDCACHE ; 
 int HCFG_LOCKTANKCACHE_MASK ; 
 int HCFG_MUTEBUTTONENABLE ; 
 scalar_t__ INTE ; 
 int /*<<< orphan*/  MICBA ; 
 int /*<<< orphan*/  MICBS ; 
 int NUM_G ; 
 int /*<<< orphan*/  PTB ; 
 int /*<<< orphan*/  PTRX ; 
 int /*<<< orphan*/  SOLEH ; 
 int /*<<< orphan*/  SOLEL ; 
 int /*<<< orphan*/  TCB ; 
 int /*<<< orphan*/  TCBS ; 
 int /*<<< orphan*/  TCBS_BUFFSIZE_16K ; 
 int /*<<< orphan*/  VTFT ; 
 int /*<<< orphan*/  outl (int,scalar_t__) ; 
 int /*<<< orphan*/  snd_emu10k1_ptr_write (struct snd_emu10k1*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 

int snd_emu10k1_done(struct snd_emu10k1 *emu)
{
	int ch;

	outl(0, emu->port + INTE);

	/*
	 *  Shutdown the chip
	 */
	for (ch = 0; ch < NUM_G; ch++)
		snd_emu10k1_ptr_write(emu, DCYSUSV, ch, 0);
	for (ch = 0; ch < NUM_G; ch++) {
		snd_emu10k1_ptr_write(emu, VTFT, ch, 0);
		snd_emu10k1_ptr_write(emu, CVCF, ch, 0);
		snd_emu10k1_ptr_write(emu, PTRX, ch, 0);
		snd_emu10k1_ptr_write(emu, CPF, ch, 0);
	}

	/* reset recording buffers */
	snd_emu10k1_ptr_write(emu, MICBS, 0, 0);
	snd_emu10k1_ptr_write(emu, MICBA, 0, 0);
	snd_emu10k1_ptr_write(emu, FXBS, 0, 0);
	snd_emu10k1_ptr_write(emu, FXBA, 0, 0);
	snd_emu10k1_ptr_write(emu, FXWC, 0, 0);
	snd_emu10k1_ptr_write(emu, ADCBS, 0, ADCBS_BUFSIZE_NONE);
	snd_emu10k1_ptr_write(emu, ADCBA, 0, 0);
	snd_emu10k1_ptr_write(emu, TCBS, 0, TCBS_BUFFSIZE_16K);
	snd_emu10k1_ptr_write(emu, TCB, 0, 0);
	if (emu->audigy)
		snd_emu10k1_ptr_write(emu, A_DBG, 0, A_DBG_SINGLE_STEP);
	else
		snd_emu10k1_ptr_write(emu, DBG, 0, EMU10K1_DBG_SINGLE_STEP);

	/* disable channel interrupt */
	snd_emu10k1_ptr_write(emu, CLIEL, 0, 0);
	snd_emu10k1_ptr_write(emu, CLIEH, 0, 0);
	snd_emu10k1_ptr_write(emu, SOLEL, 0, 0);
	snd_emu10k1_ptr_write(emu, SOLEH, 0, 0);

	/* disable audio and lock cache */
	outl(HCFG_LOCKSOUNDCACHE | HCFG_LOCKTANKCACHE_MASK | HCFG_MUTEBUTTONENABLE, emu->port + HCFG);
	snd_emu10k1_ptr_write(emu, PTB, 0, 0);

	return 0;
}