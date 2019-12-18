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
struct snd_soc_codec {int bias_level; struct aic3x_priv* private_data; } ;
struct aic3x_priv {int /*<<< orphan*/  master; } ;
typedef  enum snd_soc_bias_level { ____Placeholder_snd_soc_bias_level } snd_soc_bias_level ;

/* Variables and functions */
 int /*<<< orphan*/  AIC3X_PLL_PROGA_REG ; 
 int /*<<< orphan*/  DAC_PWR ; 
 int /*<<< orphan*/  HPLCOM_CTRL ; 
 int HPLCOM_PWR_ON ; 
 int /*<<< orphan*/  HPLOUT_CTRL ; 
 int HPLOUT_PWR_ON ; 
 int /*<<< orphan*/  HPRCOM_CTRL ; 
 int HPRCOM_PWR_ON ; 
 int /*<<< orphan*/  HPROUT_CTRL ; 
 int HPROUT_PWR_ON ; 
 int LADC_PWR_ON ; 
 int LDAC_PWR_ON ; 
 int /*<<< orphan*/  LINE1L_2_LADC_CTRL ; 
 int /*<<< orphan*/  LINE1R_2_RADC_CTRL ; 
 int /*<<< orphan*/  LLOPM_CTRL ; 
 int LLOPM_PWR_ON ; 
 int /*<<< orphan*/  MONOLOPM_CTRL ; 
 int MONOLOPM_PWR_ON ; 
 int PLL_ENABLE ; 
 int RADC_PWR_ON ; 
 int RDAC_PWR_ON ; 
 int /*<<< orphan*/  RLOPM_CTRL ; 
 int RLOPM_PWR_ON ; 
#define  SND_SOC_BIAS_OFF 131 
#define  SND_SOC_BIAS_ON 130 
#define  SND_SOC_BIAS_PREPARE 129 
#define  SND_SOC_BIAS_STANDBY 128 
 int aic3x_read_reg_cache (struct snd_soc_codec*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  aic3x_write (struct snd_soc_codec*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int aic3x_set_bias_level(struct snd_soc_codec *codec,
				enum snd_soc_bias_level level)
{
	struct aic3x_priv *aic3x = codec->private_data;
	u8 reg;

	switch (level) {
	case SND_SOC_BIAS_ON:
		/* all power is driven by DAPM system */
		if (aic3x->master) {
			/* enable pll */
			reg = aic3x_read_reg_cache(codec, AIC3X_PLL_PROGA_REG);
			aic3x_write(codec, AIC3X_PLL_PROGA_REG,
				    reg | PLL_ENABLE);
		}
		break;
	case SND_SOC_BIAS_PREPARE:
		break;
	case SND_SOC_BIAS_STANDBY:
		/*
		 * all power is driven by DAPM system,
		 * so output power is safe if bypass was set
		 */
		if (aic3x->master) {
			/* disable pll */
			reg = aic3x_read_reg_cache(codec, AIC3X_PLL_PROGA_REG);
			aic3x_write(codec, AIC3X_PLL_PROGA_REG,
				    reg & ~PLL_ENABLE);
		}
		break;
	case SND_SOC_BIAS_OFF:
		/* force all power off */
		reg = aic3x_read_reg_cache(codec, LINE1L_2_LADC_CTRL);
		aic3x_write(codec, LINE1L_2_LADC_CTRL, reg & ~LADC_PWR_ON);
		reg = aic3x_read_reg_cache(codec, LINE1R_2_RADC_CTRL);
		aic3x_write(codec, LINE1R_2_RADC_CTRL, reg & ~RADC_PWR_ON);

		reg = aic3x_read_reg_cache(codec, DAC_PWR);
		aic3x_write(codec, DAC_PWR, reg & ~(LDAC_PWR_ON | RDAC_PWR_ON));

		reg = aic3x_read_reg_cache(codec, HPLOUT_CTRL);
		aic3x_write(codec, HPLOUT_CTRL, reg & ~HPLOUT_PWR_ON);
		reg = aic3x_read_reg_cache(codec, HPROUT_CTRL);
		aic3x_write(codec, HPROUT_CTRL, reg & ~HPROUT_PWR_ON);

		reg = aic3x_read_reg_cache(codec, HPLCOM_CTRL);
		aic3x_write(codec, HPLCOM_CTRL, reg & ~HPLCOM_PWR_ON);
		reg = aic3x_read_reg_cache(codec, HPRCOM_CTRL);
		aic3x_write(codec, HPRCOM_CTRL, reg & ~HPRCOM_PWR_ON);

		reg = aic3x_read_reg_cache(codec, MONOLOPM_CTRL);
		aic3x_write(codec, MONOLOPM_CTRL, reg & ~MONOLOPM_PWR_ON);

		reg = aic3x_read_reg_cache(codec, LLOPM_CTRL);
		aic3x_write(codec, LLOPM_CTRL, reg & ~LLOPM_PWR_ON);
		reg = aic3x_read_reg_cache(codec, RLOPM_CTRL);
		aic3x_write(codec, RLOPM_CTRL, reg & ~RLOPM_PWR_ON);

		if (aic3x->master) {
			/* disable pll */
			reg = aic3x_read_reg_cache(codec, AIC3X_PLL_PROGA_REG);
			aic3x_write(codec, AIC3X_PLL_PROGA_REG,
				    reg & ~PLL_ENABLE);
		}
		break;
	}
	codec->bias_level = level;

	return 0;
}