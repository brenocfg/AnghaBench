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
typedef  int u32 ;
struct TYPE_3__ {scalar_t__ ieee_mode; } ;
struct ipw_priv {int rates_mask; TYPE_2__* ieee; TYPE_1__ assoc_request; } ;
struct TYPE_4__ {scalar_t__ mode; } ;

/* Variables and functions */
 scalar_t__ IEEE_B ; 
 scalar_t__ IPW_B_MODE ; 
 int LIBIPW_CCK_RATES_MASK ; 
#define  LIBIPW_CCK_RATE_11MB_MASK 139 
#define  LIBIPW_CCK_RATE_1MB_MASK 138 
#define  LIBIPW_CCK_RATE_2MB_MASK 137 
#define  LIBIPW_CCK_RATE_5MB_MASK 136 
#define  LIBIPW_OFDM_RATE_12MB_MASK 135 
#define  LIBIPW_OFDM_RATE_18MB_MASK 134 
#define  LIBIPW_OFDM_RATE_24MB_MASK 133 
#define  LIBIPW_OFDM_RATE_36MB_MASK 132 
#define  LIBIPW_OFDM_RATE_48MB_MASK 131 
#define  LIBIPW_OFDM_RATE_54MB_MASK 130 
#define  LIBIPW_OFDM_RATE_6MB_MASK 129 
#define  LIBIPW_OFDM_RATE_9MB_MASK 128 

__attribute__((used)) static u32 ipw_get_max_rate(struct ipw_priv *priv)
{
	u32 i = 0x80000000;
	u32 mask = priv->rates_mask;
	/* If currently associated in B mode, restrict the maximum
	 * rate match to B rates */
	if (priv->assoc_request.ieee_mode == IPW_B_MODE)
		mask &= LIBIPW_CCK_RATES_MASK;

	/* TODO: Verify that the rate is supported by the current rates
	 * list. */

	while (i && !(mask & i))
		i >>= 1;
	switch (i) {
	case LIBIPW_CCK_RATE_1MB_MASK:
		return 1000000;
	case LIBIPW_CCK_RATE_2MB_MASK:
		return 2000000;
	case LIBIPW_CCK_RATE_5MB_MASK:
		return 5500000;
	case LIBIPW_OFDM_RATE_6MB_MASK:
		return 6000000;
	case LIBIPW_OFDM_RATE_9MB_MASK:
		return 9000000;
	case LIBIPW_CCK_RATE_11MB_MASK:
		return 11000000;
	case LIBIPW_OFDM_RATE_12MB_MASK:
		return 12000000;
	case LIBIPW_OFDM_RATE_18MB_MASK:
		return 18000000;
	case LIBIPW_OFDM_RATE_24MB_MASK:
		return 24000000;
	case LIBIPW_OFDM_RATE_36MB_MASK:
		return 36000000;
	case LIBIPW_OFDM_RATE_48MB_MASK:
		return 48000000;
	case LIBIPW_OFDM_RATE_54MB_MASK:
		return 54000000;
	}

	if (priv->ieee->mode == IEEE_B)
		return 11000000;
	else
		return 54000000;
}