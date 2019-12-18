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
struct snd_es1688 {int /*<<< orphan*/  port; } ;

/* Variables and functions */
 int /*<<< orphan*/  DATA_AVAIL ; 
 int ENODEV ; 
 int /*<<< orphan*/  ES1688P (struct snd_es1688*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  READ ; 
 int /*<<< orphan*/  RESET ; 
 int inb (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  outb (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snd_es1688_dsp_command (struct snd_es1688*,int) ; 
 int /*<<< orphan*/  snd_printd (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  udelay (int) ; 

__attribute__((used)) static int snd_es1688_reset(struct snd_es1688 *chip)
{
	int i;

	outb(3, ES1688P(chip, RESET));		/* valid only for ESS chips, SB -> 1 */
	udelay(10);
	outb(0, ES1688P(chip, RESET));
	udelay(30);
	for (i = 0; i < 1000 && !(inb(ES1688P(chip, DATA_AVAIL)) & 0x80); i++);
	if (inb(ES1688P(chip, READ)) != 0xaa) {
		snd_printd("ess_reset at 0x%lx: failed!!!\n", chip->port);
		return -ENODEV;
	}
	snd_es1688_dsp_command(chip, 0xc6);	/* enable extended mode */
	return 0;
}