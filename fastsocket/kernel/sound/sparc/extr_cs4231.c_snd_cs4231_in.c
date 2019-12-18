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
struct snd_cs4231 {unsigned char mce_bit; } ;

/* Variables and functions */
 int /*<<< orphan*/  CS4231U (struct snd_cs4231*,int /*<<< orphan*/ ) ; 
 int CS4231_INIT ; 
 int /*<<< orphan*/  REG ; 
 int /*<<< orphan*/  REGSEL ; 
 unsigned char __cs4231_readb (struct snd_cs4231*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  __cs4231_writeb (struct snd_cs4231*,unsigned char,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mb () ; 
 int /*<<< orphan*/  snd_cs4231_ready (struct snd_cs4231*) ; 
 int /*<<< orphan*/  snd_printdd (char*,unsigned char) ; 

__attribute__((used)) static unsigned char snd_cs4231_in(struct snd_cs4231 *chip, unsigned char reg)
{
	snd_cs4231_ready(chip);
#ifdef CONFIG_SND_DEBUG
	if (__cs4231_readb(chip, CS4231U(chip, REGSEL)) & CS4231_INIT)
		snd_printdd("in: auto calibration time out - reg = 0x%x\n",
			    reg);
#endif
	__cs4231_writeb(chip, chip->mce_bit | reg, CS4231U(chip, REGSEL));
	mb();
	return __cs4231_readb(chip, CS4231U(chip, REG));
}