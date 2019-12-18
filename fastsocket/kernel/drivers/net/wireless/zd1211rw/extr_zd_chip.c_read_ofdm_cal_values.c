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
typedef  int /*<<< orphan*/  zd_addr_t ;
struct zd_chip {int /*<<< orphan*/ * ofdm_cal_values; } ;

/* Variables and functions */
#define  E2P_36M_CAL_VALUE1 130 
#define  E2P_48M_CAL_VALUE1 129 
#define  E2P_54M_CAL_VALUE1 128 
 int /*<<< orphan*/  E2P_CHANNEL_COUNT ; 
 int read_values (struct zd_chip*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/  const,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int read_ofdm_cal_values(struct zd_chip *chip)
{
	int r;
	int i;
	static const zd_addr_t addresses[] = {
		E2P_36M_CAL_VALUE1,
		E2P_48M_CAL_VALUE1,
		E2P_54M_CAL_VALUE1,
	};

	for (i = 0; i < 3; i++) {
		r = read_values(chip, chip->ofdm_cal_values[i],
				E2P_CHANNEL_COUNT, addresses[i], 0);
		if (r)
			return r;
	}
	return 0;
}