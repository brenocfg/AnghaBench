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
typedef  int /*<<< orphan*/  fe_spectral_inversion_t ;

/* Variables and functions */
 int /*<<< orphan*/  INVERSION_OFF ; 
 int /*<<< orphan*/  INVERSION_ON ; 
 int /*<<< orphan*/  VIT_MODE ; 
 int mt312_readreg (struct mt312_state*,int /*<<< orphan*/ ,int*) ; 

__attribute__((used)) static int mt312_get_inversion(struct mt312_state *state,
			       fe_spectral_inversion_t *i)
{
	int ret;
	u8 vit_mode;

	ret = mt312_readreg(state, VIT_MODE, &vit_mode);
	if (ret < 0)
		return ret;

	if (vit_mode & 0x80)	/* auto inversion was used */
		*i = (vit_mode & 0x40) ? INVERSION_ON : INVERSION_OFF;

	return 0;
}