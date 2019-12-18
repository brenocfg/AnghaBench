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
struct mt312_state {int dummy; } ;
typedef  int /*<<< orphan*/  fe_code_rate_t ;

/* Variables and functions */
 int /*<<< orphan*/  const FEC_1_2 ; 
 int /*<<< orphan*/  const FEC_2_3 ; 
 int /*<<< orphan*/  const FEC_3_4 ; 
 int /*<<< orphan*/  const FEC_5_6 ; 
 int /*<<< orphan*/  const FEC_6_7 ; 
 int /*<<< orphan*/  const FEC_7_8 ; 
 int /*<<< orphan*/  const FEC_AUTO ; 
 int /*<<< orphan*/  FEC_STATUS ; 
 int mt312_readreg (struct mt312_state*,int /*<<< orphan*/ ,int*) ; 

__attribute__((used)) static int mt312_get_code_rate(struct mt312_state *state, fe_code_rate_t *cr)
{
	const fe_code_rate_t fec_tab[8] =
	    { FEC_1_2, FEC_2_3, FEC_3_4, FEC_5_6, FEC_6_7, FEC_7_8,
		FEC_AUTO, FEC_AUTO };

	int ret;
	u8 fec_status;

	ret = mt312_readreg(state, FEC_STATUS, &fec_status);
	if (ret < 0)
		return ret;

	*cr = fec_tab[(fec_status >> 4) & 0x07];

	return 0;
}