#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {struct ssp_device* ssp; } ;
struct ssp_priv {TYPE_1__ dev; } ;
struct ssp_device {int dummy; } ;
struct snd_soc_dai {struct ssp_priv* private_data; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENODEV ; 
#define  PXA_SSP_AUDIO_DIV_ACDS 133 
#define  PXA_SSP_AUDIO_DIV_SCDB 132 
#define  PXA_SSP_CLK_SCDB_1 131 
#define  PXA_SSP_CLK_SCDB_4 130 
#define  PXA_SSP_CLK_SCDB_8 129 
#define  PXA_SSP_DIV_SCR 128 
 int /*<<< orphan*/  SSACD ; 
 int SSACD_ACDS (int) ; 
 int SSACD_SCDB ; 
 int SSACD_SCDX8 ; 
 int /*<<< orphan*/  cpu_is_pxa3xx () ; 
 int ssp_read_reg (struct ssp_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ssp_set_scr (struct ssp_device*,int) ; 
 int /*<<< orphan*/  ssp_write_reg (struct ssp_device*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int pxa_ssp_set_dai_clkdiv(struct snd_soc_dai *cpu_dai,
	int div_id, int div)
{
	struct ssp_priv *priv = cpu_dai->private_data;
	struct ssp_device *ssp = priv->dev.ssp;
	int val;

	switch (div_id) {
	case PXA_SSP_AUDIO_DIV_ACDS:
		val = (ssp_read_reg(ssp, SSACD) & ~0x7) | SSACD_ACDS(div);
		ssp_write_reg(ssp, SSACD, val);
		break;
	case PXA_SSP_AUDIO_DIV_SCDB:
		val = ssp_read_reg(ssp, SSACD);
		val &= ~SSACD_SCDB;
#if defined(CONFIG_PXA3xx)
		if (cpu_is_pxa3xx())
			val &= ~SSACD_SCDX8;
#endif
		switch (div) {
		case PXA_SSP_CLK_SCDB_1:
			val |= SSACD_SCDB;
			break;
		case PXA_SSP_CLK_SCDB_4:
			break;
#if defined(CONFIG_PXA3xx)
		case PXA_SSP_CLK_SCDB_8:
			if (cpu_is_pxa3xx())
				val |= SSACD_SCDX8;
			else
				return -EINVAL;
			break;
#endif
		default:
			return -EINVAL;
		}
		ssp_write_reg(ssp, SSACD, val);
		break;
	case PXA_SSP_DIV_SCR:
		ssp_set_scr(ssp, div);
		break;
	default:
		return -ENODEV;
	}

	return 0;
}