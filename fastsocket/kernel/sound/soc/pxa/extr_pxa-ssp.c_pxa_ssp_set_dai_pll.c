#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int u64 ;
typedef  int u32 ;
struct TYPE_3__ {struct ssp_device* ssp; } ;
struct ssp_priv {TYPE_1__ dev; } ;
struct ssp_device {TYPE_2__* pdev; } ;
struct snd_soc_dai {struct ssp_priv* private_data; } ;
struct TYPE_4__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  SSACD ; 
 int /*<<< orphan*/  SSACDD ; 
 scalar_t__ cpu_is_pxa3xx () ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*,int,unsigned int) ; 
 int /*<<< orphan*/  do_div (int,unsigned int) ; 
 int ssp_read_reg (struct ssp_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ssp_write_reg (struct ssp_device*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int pxa_ssp_set_dai_pll(struct snd_soc_dai *cpu_dai,
	int pll_id, unsigned int freq_in, unsigned int freq_out)
{
	struct ssp_priv *priv = cpu_dai->private_data;
	struct ssp_device *ssp = priv->dev.ssp;
	u32 ssacd = ssp_read_reg(ssp, SSACD) & ~0x70;

#if defined(CONFIG_PXA3xx)
	if (cpu_is_pxa3xx())
		ssp_write_reg(ssp, SSACDD, 0);
#endif

	switch (freq_out) {
	case 5622000:
		break;
	case 11345000:
		ssacd |= (0x1 << 4);
		break;
	case 12235000:
		ssacd |= (0x2 << 4);
		break;
	case 14857000:
		ssacd |= (0x3 << 4);
		break;
	case 32842000:
		ssacd |= (0x4 << 4);
		break;
	case 48000000:
		ssacd |= (0x5 << 4);
		break;
	case 0:
		/* Disable */
		break;

	default:
#ifdef CONFIG_PXA3xx
		/* PXA3xx has a clock ditherer which can be used to generate
		 * a wider range of frequencies - calculate a value for it.
		 */
		if (cpu_is_pxa3xx()) {
			u32 val;
			u64 tmp = 19968;
			tmp *= 1000000;
			do_div(tmp, freq_out);
			val = tmp;

			val = (val << 16) | 64;
			ssp_write_reg(ssp, SSACDD, val);

			ssacd |= (0x6 << 4);

			dev_dbg(&ssp->pdev->dev,
				"Using SSACDD %x to supply %uHz\n",
				val, freq_out);
			break;
		}
#endif

		return -EINVAL;
	}

	ssp_write_reg(ssp, SSACD, ssacd);

	return 0;
}