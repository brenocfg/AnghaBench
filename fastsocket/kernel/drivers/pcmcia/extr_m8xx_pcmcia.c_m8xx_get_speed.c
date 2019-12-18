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
typedef  int u32 ;

/* Variables and functions */
 int ADJ ; 
 int PCMCIA_BMT_LIMIT ; 
 int /*<<< orphan*/  printk (char*) ; 

__attribute__((used)) static u32 m8xx_get_speed(u32 ns, u32 is_io, u32 bus_freq)
{
	u32 reg, clocks, psst, psl, psht;

	if (!ns) {

		/*
		 * We get called with IO maps setup to 0ns
		 * if not specified by the user.
		 * They should be 255ns.
		 */

		if (is_io)
			ns = 255;
		else
			ns = 100;	/* fast memory if 0 */
	}

	/*
	 * In PSST, PSL, PSHT fields we tell the controller
	 * timing parameters in CLKOUT clock cycles.
	 * CLKOUT is the same as GCLK2_50.
	 */

/* how we want to adjust the timing - in percent */

#define ADJ 180			/* 80 % longer accesstime - to be sure */

	clocks = ((bus_freq / 1000) * ns) / 1000;
	clocks = (clocks * ADJ) / (100 * 1000);
	if (clocks >= PCMCIA_BMT_LIMIT) {
		printk("Max access time limit reached\n");
		clocks = PCMCIA_BMT_LIMIT - 1;
	}

	psst = clocks / 7;	/* setup time */
	psht = clocks / 7;	/* hold time */
	psl = (clocks * 5) / 7;	/* strobe length */

	psst += clocks - (psst + psht + psl);

	reg = psst << 12;
	reg |= psl << 7;
	reg |= psht << 16;

	return reg;
}