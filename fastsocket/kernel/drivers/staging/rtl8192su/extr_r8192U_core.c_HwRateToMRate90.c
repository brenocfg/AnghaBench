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
 int /*<<< orphan*/  COMP_RECV ; 
#define  DESC90_RATE11M 156 
#define  DESC90_RATE12M 155 
#define  DESC90_RATE18M 154 
#define  DESC90_RATE1M 153 
#define  DESC90_RATE24M 152 
#define  DESC90_RATE2M 151 
#define  DESC90_RATE36M 150 
#define  DESC90_RATE48M 149 
#define  DESC90_RATE54M 148 
#define  DESC90_RATE5_5M 147 
#define  DESC90_RATE6M 146 
#define  DESC90_RATE9M 145 
#define  DESC90_RATEMCS0 144 
#define  DESC90_RATEMCS1 143 
#define  DESC90_RATEMCS10 142 
#define  DESC90_RATEMCS11 141 
#define  DESC90_RATEMCS12 140 
#define  DESC90_RATEMCS13 139 
#define  DESC90_RATEMCS14 138 
#define  DESC90_RATEMCS15 137 
#define  DESC90_RATEMCS2 136 
#define  DESC90_RATEMCS3 135 
#define  DESC90_RATEMCS32 134 
#define  DESC90_RATEMCS4 133 
#define  DESC90_RATEMCS5 132 
#define  DESC90_RATEMCS6 131 
#define  DESC90_RATEMCS7 130 
#define  DESC90_RATEMCS8 129 
#define  DESC90_RATEMCS9 128 
 int MGN_11M ; 
 int MGN_12M ; 
 int MGN_18M ; 
 int MGN_1M ; 
 int MGN_24M ; 
 int MGN_2M ; 
 int MGN_36M ; 
 int MGN_48M ; 
 int MGN_54M ; 
 int MGN_5_5M ; 
 int MGN_6M ; 
 int MGN_9M ; 
 int MGN_MCS0 ; 
 int MGN_MCS1 ; 
 int MGN_MCS10 ; 
 int MGN_MCS11 ; 
 int MGN_MCS12 ; 
 int MGN_MCS13 ; 
 int MGN_MCS14 ; 
 int MGN_MCS15 ; 
 int MGN_MCS2 ; 
 int MGN_MCS3 ; 
 int MGN_MCS4 ; 
 int MGN_MCS5 ; 
 int MGN_MCS6 ; 
 int MGN_MCS7 ; 
 int MGN_MCS8 ; 
 int MGN_MCS9 ; 
 int /*<<< orphan*/  RT_TRACE (int /*<<< orphan*/ ,char*,int,int) ; 

u8 HwRateToMRate90(bool bIsHT, u8 rate)
{
	u8  ret_rate = 0xff;

	if(!bIsHT) {
		switch(rate) {
			case DESC90_RATE1M:   ret_rate = MGN_1M;         break;
			case DESC90_RATE2M:   ret_rate = MGN_2M;         break;
			case DESC90_RATE5_5M: ret_rate = MGN_5_5M;       break;
			case DESC90_RATE11M:  ret_rate = MGN_11M;        break;
			case DESC90_RATE6M:   ret_rate = MGN_6M;         break;
			case DESC90_RATE9M:   ret_rate = MGN_9M;         break;
			case DESC90_RATE12M:  ret_rate = MGN_12M;        break;
			case DESC90_RATE18M:  ret_rate = MGN_18M;        break;
			case DESC90_RATE24M:  ret_rate = MGN_24M;        break;
			case DESC90_RATE36M:  ret_rate = MGN_36M;        break;
			case DESC90_RATE48M:  ret_rate = MGN_48M;        break;
			case DESC90_RATE54M:  ret_rate = MGN_54M;        break;

			default:
				ret_rate = 0xff;
				RT_TRACE(COMP_RECV, "HwRateToMRate90(): Non supported Rate [%x], bIsHT = %d!!!\n", rate, bIsHT);
				break;
		}

	} else {
		switch(rate) {
			case DESC90_RATEMCS0:   ret_rate = MGN_MCS0;    break;
			case DESC90_RATEMCS1:   ret_rate = MGN_MCS1;    break;
			case DESC90_RATEMCS2:   ret_rate = MGN_MCS2;    break;
			case DESC90_RATEMCS3:   ret_rate = MGN_MCS3;    break;
			case DESC90_RATEMCS4:   ret_rate = MGN_MCS4;    break;
			case DESC90_RATEMCS5:   ret_rate = MGN_MCS5;    break;
			case DESC90_RATEMCS6:   ret_rate = MGN_MCS6;    break;
			case DESC90_RATEMCS7:   ret_rate = MGN_MCS7;    break;
			case DESC90_RATEMCS8:   ret_rate = MGN_MCS8;    break;
			case DESC90_RATEMCS9:   ret_rate = MGN_MCS9;    break;
			case DESC90_RATEMCS10:  ret_rate = MGN_MCS10;   break;
			case DESC90_RATEMCS11:  ret_rate = MGN_MCS11;   break;
			case DESC90_RATEMCS12:  ret_rate = MGN_MCS12;   break;
			case DESC90_RATEMCS13:  ret_rate = MGN_MCS13;   break;
			case DESC90_RATEMCS14:  ret_rate = MGN_MCS14;   break;
			case DESC90_RATEMCS15:  ret_rate = MGN_MCS15;   break;
			case DESC90_RATEMCS32:  ret_rate = (0x80|0x20); break;

			default:
				ret_rate = 0xff;
				RT_TRACE(COMP_RECV, "HwRateToMRate90(): Non supported Rate [%x], bIsHT = %d!!!\n",rate, bIsHT);
				break;
		}
	}

	return ret_rate;
}