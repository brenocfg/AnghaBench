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
typedef  int /*<<< orphan*/  u16 ;

/* Variables and functions */
 int /*<<< orphan*/  B43_WARN_ON (int) ; 
 int /*<<< orphan*/ * b43_radio_channel_codes_bg ; 

__attribute__((used)) static inline u16 channel2freq_bg(u8 channel)
{
	B43_WARN_ON(!(channel >= 1 && channel <= 14));

	return b43_radio_channel_codes_bg[channel - 1];
}