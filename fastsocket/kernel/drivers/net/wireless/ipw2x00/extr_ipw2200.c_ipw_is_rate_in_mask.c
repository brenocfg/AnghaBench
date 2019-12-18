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
struct ipw_priv {int rates_mask; } ;

/* Variables and functions */
 int IEEE_A ; 
 int IEEE_B ; 
 int LIBIPW_BASIC_RATE_MASK ; 
#define  LIBIPW_CCK_RATE_11MB 139 
 int LIBIPW_CCK_RATE_11MB_MASK ; 
#define  LIBIPW_CCK_RATE_1MB 138 
 int LIBIPW_CCK_RATE_1MB_MASK ; 
#define  LIBIPW_CCK_RATE_2MB 137 
 int LIBIPW_CCK_RATE_2MB_MASK ; 
#define  LIBIPW_CCK_RATE_5MB 136 
 int LIBIPW_CCK_RATE_5MB_MASK ; 
#define  LIBIPW_OFDM_RATE_12MB 135 
 int LIBIPW_OFDM_RATE_12MB_MASK ; 
#define  LIBIPW_OFDM_RATE_18MB 134 
 int LIBIPW_OFDM_RATE_18MB_MASK ; 
#define  LIBIPW_OFDM_RATE_24MB 133 
 int LIBIPW_OFDM_RATE_24MB_MASK ; 
#define  LIBIPW_OFDM_RATE_36MB 132 
 int LIBIPW_OFDM_RATE_36MB_MASK ; 
#define  LIBIPW_OFDM_RATE_48MB 131 
 int LIBIPW_OFDM_RATE_48MB_MASK ; 
#define  LIBIPW_OFDM_RATE_54MB 130 
 int LIBIPW_OFDM_RATE_54MB_MASK ; 
#define  LIBIPW_OFDM_RATE_6MB 129 
 int LIBIPW_OFDM_RATE_6MB_MASK ; 
#define  LIBIPW_OFDM_RATE_9MB 128 
 int LIBIPW_OFDM_RATE_9MB_MASK ; 

__attribute__((used)) static int ipw_is_rate_in_mask(struct ipw_priv *priv, int ieee_mode, u8 rate)
{
	rate &= ~LIBIPW_BASIC_RATE_MASK;
	if (ieee_mode == IEEE_A) {
		switch (rate) {
		case LIBIPW_OFDM_RATE_6MB:
			return priv->rates_mask & LIBIPW_OFDM_RATE_6MB_MASK ?
			    1 : 0;
		case LIBIPW_OFDM_RATE_9MB:
			return priv->rates_mask & LIBIPW_OFDM_RATE_9MB_MASK ?
			    1 : 0;
		case LIBIPW_OFDM_RATE_12MB:
			return priv->
			    rates_mask & LIBIPW_OFDM_RATE_12MB_MASK ? 1 : 0;
		case LIBIPW_OFDM_RATE_18MB:
			return priv->
			    rates_mask & LIBIPW_OFDM_RATE_18MB_MASK ? 1 : 0;
		case LIBIPW_OFDM_RATE_24MB:
			return priv->
			    rates_mask & LIBIPW_OFDM_RATE_24MB_MASK ? 1 : 0;
		case LIBIPW_OFDM_RATE_36MB:
			return priv->
			    rates_mask & LIBIPW_OFDM_RATE_36MB_MASK ? 1 : 0;
		case LIBIPW_OFDM_RATE_48MB:
			return priv->
			    rates_mask & LIBIPW_OFDM_RATE_48MB_MASK ? 1 : 0;
		case LIBIPW_OFDM_RATE_54MB:
			return priv->
			    rates_mask & LIBIPW_OFDM_RATE_54MB_MASK ? 1 : 0;
		default:
			return 0;
		}
	}

	/* B and G mixed */
	switch (rate) {
	case LIBIPW_CCK_RATE_1MB:
		return priv->rates_mask & LIBIPW_CCK_RATE_1MB_MASK ? 1 : 0;
	case LIBIPW_CCK_RATE_2MB:
		return priv->rates_mask & LIBIPW_CCK_RATE_2MB_MASK ? 1 : 0;
	case LIBIPW_CCK_RATE_5MB:
		return priv->rates_mask & LIBIPW_CCK_RATE_5MB_MASK ? 1 : 0;
	case LIBIPW_CCK_RATE_11MB:
		return priv->rates_mask & LIBIPW_CCK_RATE_11MB_MASK ? 1 : 0;
	}

	/* If we are limited to B modulations, bail at this point */
	if (ieee_mode == IEEE_B)
		return 0;

	/* G */
	switch (rate) {
	case LIBIPW_OFDM_RATE_6MB:
		return priv->rates_mask & LIBIPW_OFDM_RATE_6MB_MASK ? 1 : 0;
	case LIBIPW_OFDM_RATE_9MB:
		return priv->rates_mask & LIBIPW_OFDM_RATE_9MB_MASK ? 1 : 0;
	case LIBIPW_OFDM_RATE_12MB:
		return priv->rates_mask & LIBIPW_OFDM_RATE_12MB_MASK ? 1 : 0;
	case LIBIPW_OFDM_RATE_18MB:
		return priv->rates_mask & LIBIPW_OFDM_RATE_18MB_MASK ? 1 : 0;
	case LIBIPW_OFDM_RATE_24MB:
		return priv->rates_mask & LIBIPW_OFDM_RATE_24MB_MASK ? 1 : 0;
	case LIBIPW_OFDM_RATE_36MB:
		return priv->rates_mask & LIBIPW_OFDM_RATE_36MB_MASK ? 1 : 0;
	case LIBIPW_OFDM_RATE_48MB:
		return priv->rates_mask & LIBIPW_OFDM_RATE_48MB_MASK ? 1 : 0;
	case LIBIPW_OFDM_RATE_54MB:
		return priv->rates_mask & LIBIPW_OFDM_RATE_54MB_MASK ? 1 : 0;
	}

	return 0;
}