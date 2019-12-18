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
typedef  int u8 ;
struct hda_codec {struct ca0132_spec* spec; } ;
struct ca0132_spec {int dmic_ctl; int /*<<< orphan*/ * input_pins; } ;

/* Variables and functions */
 int /*<<< orphan*/  VENDOR_CHIPIO_DMIC_CTL_SET ; 
 int /*<<< orphan*/  VENDOR_CHIPIO_DMIC_MCLK_SET ; 
 int /*<<< orphan*/  VENDOR_CHIPIO_DMIC_PIN_SET ; 
 int /*<<< orphan*/  snd_hda_codec_write (struct hda_codec*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void ca0132_init_dmic(struct hda_codec *codec)
{
	struct ca0132_spec *spec = codec->spec;
	u8 val;

	/* Setup Digital Mic here, but don't enable.
	 * Enable based on jack detect.
	 */

	/* MCLK uses MPIO1, set to enable.
	 * Bit 2-0: MPIO select
	 * Bit   3: set to disable
	 * Bit 7-4: reserved
	 */
	val = 0x01;
	snd_hda_codec_write(codec, spec->input_pins[0], 0,
			    VENDOR_CHIPIO_DMIC_MCLK_SET, val);

	/* Data1 uses MPIO3. Data2 not use
	 * Bit 2-0: Data1 MPIO select
	 * Bit   3: set disable Data1
	 * Bit 6-4: Data2 MPIO select
	 * Bit   7: set disable Data2
	 */
	val = 0x83;
	snd_hda_codec_write(codec, spec->input_pins[0], 0,
			    VENDOR_CHIPIO_DMIC_PIN_SET, val);

	/* Use Ch-0 and Ch-1. Rate is 48K, mode 1. Disable DMic first.
	 * Bit 3-0: Channel mask
	 * Bit   4: set for 48KHz, clear for 32KHz
	 * Bit   5: mode
	 * Bit   6: set to select Data2, clear for Data1
	 * Bit   7: set to enable DMic, clear for AMic
	 */
	val = 0x23;
	/* keep a copy of dmic ctl val for enable/disable dmic purpuse */
	spec->dmic_ctl = val;
	snd_hda_codec_write(codec, spec->input_pins[0], 0,
			    VENDOR_CHIPIO_DMIC_CTL_SET, val);
}