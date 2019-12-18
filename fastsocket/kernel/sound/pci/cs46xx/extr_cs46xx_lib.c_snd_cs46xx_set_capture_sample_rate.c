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
struct snd_cs46xx {int /*<<< orphan*/  reg_lock; } ;

/* Variables and functions */
 scalar_t__ BA1_CCI ; 
 scalar_t__ BA1_CCST ; 
 scalar_t__ BA1_CD ; 
 scalar_t__ BA1_CFG1 ; 
 scalar_t__ BA1_CFG2 ; 
 scalar_t__ BA1_CPI ; 
 scalar_t__ BA1_CSPB ; 
 scalar_t__ BA1_CSRC ; 
 unsigned int BA1_VARIDEC_BUF_1 ; 
 unsigned int GOF_PER_SEC ; 
 int /*<<< orphan*/  snd_cs46xx_poke (struct snd_cs46xx*,scalar_t__,int) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static void snd_cs46xx_set_capture_sample_rate(struct snd_cs46xx *chip, unsigned int rate)
{
	unsigned long flags;
	unsigned int phiIncr, coeffIncr, tmp1, tmp2;
	unsigned int correctionPerGOF, correctionPerSec, initialDelay;
	unsigned int frameGroupLength, cnt;

	/*
	 *  We can only decimate by up to a factor of 1/9th the hardware rate.
	 *  Correct the value if an attempt is made to stray outside that limit.
	 */
	if ((rate * 9) < 48000)
		rate = 48000 / 9;

	/*
	 *  We can not capture at at rate greater than the Input Rate (48000).
	 *  Return an error if an attempt is made to stray outside that limit.
	 */
	if (rate > 48000)
		rate = 48000;

	/*
	 *  Compute the values used to drive the actual sample rate conversion.
	 *  The following formulas are being computed, using inline assembly
	 *  since we need to use 64 bit arithmetic to compute the values:
	 *
	 *     coeffIncr = -floor((Fs,out * 2^23) / Fs,in)
	 *     phiIncr = floor((Fs,in * 2^26) / Fs,out)
	 *     correctionPerGOF = floor((Fs,in * 2^26 - Fs,out * phiIncr) /
	 *                                GOF_PER_SEC)
	 *     correctionPerSec = Fs,in * 2^26 - Fs,out * phiIncr -
	 *                          GOF_PER_SEC * correctionPerGOF
	 *     initialDelay = ceil((24 * Fs,in) / Fs,out)
	 *
	 * i.e.
	 *
	 *     coeffIncr = neg(dividend((Fs,out * 2^23) / Fs,in))
	 *     phiIncr:ulOther = dividend:remainder((Fs,in * 2^26) / Fs,out)
	 *     correctionPerGOF:correctionPerSec =
	 * 	    dividend:remainder(ulOther / GOF_PER_SEC)
	 *     initialDelay = dividend(((24 * Fs,in) + Fs,out - 1) / Fs,out)
	 */

	tmp1 = rate << 16;
	coeffIncr = tmp1 / 48000;
	tmp1 -= coeffIncr * 48000;
	tmp1 <<= 7;
	coeffIncr <<= 7;
	coeffIncr += tmp1 / 48000;
	coeffIncr ^= 0xFFFFFFFF;
	coeffIncr++;
	tmp1 = 48000 << 16;
	phiIncr = tmp1 / rate;
	tmp1 -= phiIncr * rate;
	tmp1 <<= 10;
	phiIncr <<= 10;
	tmp2 = tmp1 / rate;
	phiIncr += tmp2;
	tmp1 -= tmp2 * rate;
	correctionPerGOF = tmp1 / GOF_PER_SEC;
	tmp1 -= correctionPerGOF * GOF_PER_SEC;
	correctionPerSec = tmp1;
	initialDelay = ((48000 * 24) + rate - 1) / rate;

	/*
	 *  Fill in the VariDecimate control block.
	 */
	spin_lock_irqsave(&chip->reg_lock, flags);
	snd_cs46xx_poke(chip, BA1_CSRC,
		((correctionPerSec << 16) & 0xFFFF0000) | (correctionPerGOF & 0xFFFF));
	snd_cs46xx_poke(chip, BA1_CCI, coeffIncr);
	snd_cs46xx_poke(chip, BA1_CD,
		(((BA1_VARIDEC_BUF_1 + (initialDelay << 2)) << 16) & 0xFFFF0000) | 0x80);
	snd_cs46xx_poke(chip, BA1_CPI, phiIncr);
	spin_unlock_irqrestore(&chip->reg_lock, flags);

	/*
	 *  Figure out the frame group length for the write back task.  Basically,
	 *  this is just the factors of 24000 (2^6*3*5^3) that are not present in
	 *  the output sample rate.
	 */
	frameGroupLength = 1;
	for (cnt = 2; cnt <= 64; cnt *= 2) {
		if (((rate / cnt) * cnt) != rate)
			frameGroupLength *= 2;
	}
	if (((rate / 3) * 3) != rate) {
		frameGroupLength *= 3;
	}
	for (cnt = 5; cnt <= 125; cnt *= 5) {
		if (((rate / cnt) * cnt) != rate) 
			frameGroupLength *= 5;
        }

	/*
	 * Fill in the WriteBack control block.
	 */
	spin_lock_irqsave(&chip->reg_lock, flags);
	snd_cs46xx_poke(chip, BA1_CFG1, frameGroupLength);
	snd_cs46xx_poke(chip, BA1_CFG2, (0x00800000 | frameGroupLength));
	snd_cs46xx_poke(chip, BA1_CCST, 0x0000FFFF);
	snd_cs46xx_poke(chip, BA1_CSPB, ((65536 * rate) / 24000));
	snd_cs46xx_poke(chip, (BA1_CSPB + 4), 0x0000FFFF);
	spin_unlock_irqrestore(&chip->reg_lock, flags);
}