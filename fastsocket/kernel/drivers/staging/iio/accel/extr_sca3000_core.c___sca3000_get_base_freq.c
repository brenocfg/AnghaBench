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
struct sca3000_state {int dummy; } ;
struct sca3000_chip_info {int measurement_mode_freq; int option_mode_1_freq; int option_mode_2_freq; } ;

/* Variables and functions */
#define  SCA3000_MEAS_MODE_NORMAL 130 
#define  SCA3000_MEAS_MODE_OP_1 129 
#define  SCA3000_MEAS_MODE_OP_2 128 
 int /*<<< orphan*/  SCA3000_REG_ADDR_MODE ; 
 int /*<<< orphan*/  kfree (int*) ; 
 int sca3000_read_data (struct sca3000_state*,int /*<<< orphan*/ ,int**,int) ; 

__attribute__((used)) static inline int __sca3000_get_base_freq(struct sca3000_state *st,
					  const struct sca3000_chip_info *info,
					  int *base_freq)
{
	int ret;
	u8 *rx;

	ret = sca3000_read_data(st, SCA3000_REG_ADDR_MODE, &rx, 1);
	if (ret)
		goto error_ret;
	switch (0x03 & rx[1]) {
	case SCA3000_MEAS_MODE_NORMAL:
		*base_freq = info->measurement_mode_freq;
		break;
	case SCA3000_MEAS_MODE_OP_1:
		*base_freq = info->option_mode_1_freq;
		break;
	case SCA3000_MEAS_MODE_OP_2:
		*base_freq = info->option_mode_2_freq;
		break;
	};
	kfree(rx);
error_ret:
	return ret;
}