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
typedef  int u16 ;
struct ac97_codec {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  AC97_POWER_CONTROL ; 
 int POLL_COUNT ; 
 int /*<<< orphan*/  PSC_AC97STAT ; 
 int PSC_AC97STAT_CR ; 
 int /*<<< orphan*/  au1550_delay (int) ; 
 int au_readl (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  au_sync () ; 
 int /*<<< orphan*/  err (char*,...) ; 
 int rdcodec (struct ac97_codec*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wrcodec (struct ac97_codec*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
waitcodec(struct ac97_codec *codec)
{
	u16	temp;
	u32	val;
	int	i;

	/* codec_wait is used to wait for a ready state after
	 * an AC97C_RESET.
	 */
	au1550_delay(10);

	/* first poll the CODEC_READY tag bit
	*/
	for (i = 0; i < POLL_COUNT; i++) {
		val = au_readl(PSC_AC97STAT);
		au_sync();
		if (val & PSC_AC97STAT_CR)
			break;
	}
	if (i == POLL_COUNT) {
		err("waitcodec: CODEC_READY poll expired!");
		return;
	}

	/* get AC'97 powerdown control/status register
	*/
	temp = rdcodec(codec, AC97_POWER_CONTROL);

	/* If anything is powered down, power'em up
	*/
	if (temp & 0x7f00) {
		/* Power on
		*/
		wrcodec(codec, AC97_POWER_CONTROL, 0);
		au1550_delay(100);

		/* Reread
		*/
		temp = rdcodec(codec, AC97_POWER_CONTROL);
	}

	/* Check if Codec REF,ANL,DAC,ADC ready
	*/
	if ((temp & 0x7f0f) != 0x000f)
		err("codec reg 26 status (0x%x) not ready!!", temp);
}