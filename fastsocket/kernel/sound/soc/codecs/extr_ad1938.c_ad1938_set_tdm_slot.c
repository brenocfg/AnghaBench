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
struct snd_soc_dai {struct snd_soc_codec* codec; } ;
struct snd_soc_codec {int (* read ) (struct snd_soc_codec*,int /*<<< orphan*/ ) ;int /*<<< orphan*/  (* write ) (struct snd_soc_codec*,int /*<<< orphan*/ ,int) ;} ;

/* Variables and functions */
 int AD1938_ADC_16_CHANNELS ; 
 int AD1938_ADC_2_CHANNELS ; 
 int AD1938_ADC_4_CHANNELS ; 
 int AD1938_ADC_8_CHANNELS ; 
 int AD1938_ADC_CHAN_MASK ; 
 int AD1938_ADC_CHAN_SHFT ; 
 int /*<<< orphan*/  AD1938_ADC_CTRL2 ; 
 int AD1938_DAC_16_CHANNELS ; 
 int AD1938_DAC_2_CHANNELS ; 
 int AD1938_DAC_4_CHANNELS ; 
 int AD1938_DAC_8_CHANNELS ; 
 int AD1938_DAC_CHAN_MASK ; 
 int AD1938_DAC_CHAN_SHFT ; 
 int /*<<< orphan*/  AD1938_DAC_CTRL1 ; 
 int EINVAL ; 
 int stub1 (struct snd_soc_codec*,int /*<<< orphan*/ ) ; 
 int stub2 (struct snd_soc_codec*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub3 (struct snd_soc_codec*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  stub4 (struct snd_soc_codec*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int ad1938_set_tdm_slot(struct snd_soc_dai *dai, unsigned int tx_mask,
			       unsigned int mask, int slots, int width)
{
	struct snd_soc_codec *codec = dai->codec;
	int dac_reg = codec->read(codec, AD1938_DAC_CTRL1);
	int adc_reg = codec->read(codec, AD1938_ADC_CTRL2);

	dac_reg &= ~AD1938_DAC_CHAN_MASK;
	adc_reg &= ~AD1938_ADC_CHAN_MASK;

	switch (slots) {
	case 2:
		dac_reg |= AD1938_DAC_2_CHANNELS << AD1938_DAC_CHAN_SHFT;
		adc_reg |= AD1938_ADC_2_CHANNELS << AD1938_ADC_CHAN_SHFT;
		break;
	case 4:
		dac_reg |= AD1938_DAC_4_CHANNELS << AD1938_DAC_CHAN_SHFT;
		adc_reg |= AD1938_ADC_4_CHANNELS << AD1938_ADC_CHAN_SHFT;
		break;
	case 8:
		dac_reg |= AD1938_DAC_8_CHANNELS << AD1938_DAC_CHAN_SHFT;
		adc_reg |= AD1938_ADC_8_CHANNELS << AD1938_ADC_CHAN_SHFT;
		break;
	case 16:
		dac_reg |= AD1938_DAC_16_CHANNELS << AD1938_DAC_CHAN_SHFT;
		adc_reg |= AD1938_ADC_16_CHANNELS << AD1938_ADC_CHAN_SHFT;
		break;
	default:
		return -EINVAL;
	}

	codec->write(codec, AD1938_DAC_CTRL1, dac_reg);
	codec->write(codec, AD1938_ADC_CTRL2, adc_reg);

	return 0;
}