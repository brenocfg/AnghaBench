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
#define  B43legacy_CCK_RATE_11MB 131 
#define  B43legacy_CCK_RATE_1MB 130 
#define  B43legacy_CCK_RATE_2MB 129 
#define  B43legacy_CCK_RATE_5MB 128 

u8 b43legacy_plcp_get_ratecode_cck(const u8 bitrate)
{
	switch (bitrate) {
	case B43legacy_CCK_RATE_1MB:
		return 0x0A;
	case B43legacy_CCK_RATE_2MB:
		return 0x14;
	case B43legacy_CCK_RATE_5MB:
		return 0x37;
	case B43legacy_CCK_RATE_11MB:
		return 0x6E;
	}
	B43legacy_BUG_ON(1);
	return 0;
}