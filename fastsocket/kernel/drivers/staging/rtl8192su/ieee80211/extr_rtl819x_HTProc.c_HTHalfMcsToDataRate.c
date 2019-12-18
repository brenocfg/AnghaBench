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
typedef  size_t u8 ;
typedef  int /*<<< orphan*/  u16 ;
struct ieee80211_device {int dummy; } ;

/* Variables and functions */
 scalar_t__ IsHTHalfNmode40Bandwidth (struct ieee80211_device*) ; 
 scalar_t__ IsHTHalfNmodeSGI (struct ieee80211_device*,size_t) ; 
 int /*<<< orphan*/ *** MCS_DATA_RATE ; 

u16 HTHalfMcsToDataRate(struct ieee80211_device* ieee, 	u8	nMcsRate)
{

	u8	is40MHz;
	u8	isShortGI;

	is40MHz  =  (IsHTHalfNmode40Bandwidth(ieee))?1:0;
	isShortGI = (IsHTHalfNmodeSGI(ieee, is40MHz))? 1:0;

	return MCS_DATA_RATE[is40MHz][isShortGI][(nMcsRate&0x7f)];
}