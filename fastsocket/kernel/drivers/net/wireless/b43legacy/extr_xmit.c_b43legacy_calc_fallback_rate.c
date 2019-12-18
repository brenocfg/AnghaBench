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

/* Variables and functions */
 int /*<<< orphan*/  B43legacy_BUG_ON (int) ; 
#define  B43legacy_CCK_RATE_11MB 139 
#define  B43legacy_CCK_RATE_1MB 138 
#define  B43legacy_CCK_RATE_2MB 137 
#define  B43legacy_CCK_RATE_5MB 136 
#define  B43legacy_OFDM_RATE_12MB 135 
#define  B43legacy_OFDM_RATE_18MB 134 
#define  B43legacy_OFDM_RATE_24MB 133 
#define  B43legacy_OFDM_RATE_36MB 132 
#define  B43legacy_OFDM_RATE_48MB 131 
#define  B43legacy_OFDM_RATE_54MB 130 
#define  B43legacy_OFDM_RATE_6MB 129 
#define  B43legacy_OFDM_RATE_9MB 128 

__attribute__((used)) static u8 b43legacy_calc_fallback_rate(u8 bitrate)
{
	switch (bitrate) {
	case B43legacy_CCK_RATE_1MB:
		return B43legacy_CCK_RATE_1MB;
	case B43legacy_CCK_RATE_2MB:
		return B43legacy_CCK_RATE_1MB;
	case B43legacy_CCK_RATE_5MB:
		return B43legacy_CCK_RATE_2MB;
	case B43legacy_CCK_RATE_11MB:
		return B43legacy_CCK_RATE_5MB;
	case B43legacy_OFDM_RATE_6MB:
		return B43legacy_CCK_RATE_5MB;
	case B43legacy_OFDM_RATE_9MB:
		return B43legacy_OFDM_RATE_6MB;
	case B43legacy_OFDM_RATE_12MB:
		return B43legacy_OFDM_RATE_9MB;
	case B43legacy_OFDM_RATE_18MB:
		return B43legacy_OFDM_RATE_12MB;
	case B43legacy_OFDM_RATE_24MB:
		return B43legacy_OFDM_RATE_18MB;
	case B43legacy_OFDM_RATE_36MB:
		return B43legacy_OFDM_RATE_24MB;
	case B43legacy_OFDM_RATE_48MB:
		return B43legacy_OFDM_RATE_36MB;
	case B43legacy_OFDM_RATE_54MB:
		return B43legacy_OFDM_RATE_48MB;
	}
	B43legacy_BUG_ON(1);
	return 0;
}