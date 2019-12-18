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
struct pinmux_info {struct pinmux_cfg_reg* cfg_regs; } ;
struct pinmux_cfg_reg {unsigned long reg_width; unsigned long field_width; scalar_t__* enum_ids; unsigned long* cnt; } ;
typedef  scalar_t__ pinmux_enum_t ;

/* Variables and functions */

__attribute__((used)) static int get_config_reg(struct pinmux_info *gpioc, pinmux_enum_t enum_id,
			  struct pinmux_cfg_reg **crp, int *indexp,
			  unsigned long **cntp)
{
	struct pinmux_cfg_reg *config_reg;
	unsigned long r_width, f_width;
	int k, n;

	k = 0;
	while (1) {
		config_reg = gpioc->cfg_regs + k;

		r_width = config_reg->reg_width;
		f_width = config_reg->field_width;

		if (!r_width)
			break;
		for (n = 0; n < (r_width / f_width) * 1 << f_width; n++) {
			if (config_reg->enum_ids[n] == enum_id) {
				*crp = config_reg;
				*indexp = n;
				*cntp = &config_reg->cnt[n / (1 << f_width)];
				return 0;
			}
		}
		k++;
	}

	return -1;
}