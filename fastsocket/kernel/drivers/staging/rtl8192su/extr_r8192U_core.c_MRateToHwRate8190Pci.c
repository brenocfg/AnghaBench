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
 int DESC92S_RATE11M ; 
 int DESC92S_RATE12M ; 
 int DESC92S_RATE18M ; 
 int DESC92S_RATE1M ; 
 int DESC92S_RATE24M ; 
 int DESC92S_RATE2M ; 
 int DESC92S_RATE36M ; 
 int DESC92S_RATE48M ; 
 int DESC92S_RATE54M ; 
 int DESC92S_RATE5_5M ; 
 int DESC92S_RATE6M ; 
 int DESC92S_RATE9M ; 
 int DESC92S_RATEMCS0 ; 
 int DESC92S_RATEMCS1 ; 
 int DESC92S_RATEMCS10 ; 
 int DESC92S_RATEMCS11 ; 
 int DESC92S_RATEMCS12 ; 
 int DESC92S_RATEMCS13 ; 
 int DESC92S_RATEMCS14 ; 
 int DESC92S_RATEMCS15 ; 
 int DESC92S_RATEMCS15_SG ; 
 int DESC92S_RATEMCS2 ; 
 int DESC92S_RATEMCS3 ; 
 int DESC92S_RATEMCS4 ; 
 int DESC92S_RATEMCS5 ; 
 int DESC92S_RATEMCS6 ; 
 int DESC92S_RATEMCS7 ; 
 int DESC92S_RATEMCS8 ; 
 int DESC92S_RATEMCS9 ; 
#define  MGN_11M 171 
#define  MGN_12M 170 
#define  MGN_18M 169 
#define  MGN_1M 168 
#define  MGN_24M 167 
#define  MGN_2M 166 
#define  MGN_36M 165 
#define  MGN_48M 164 
#define  MGN_54M 163 
#define  MGN_5_5M 162 
#define  MGN_6M 161 
#define  MGN_9M 160 
#define  MGN_MCS0 159 
#define  MGN_MCS0_SG 158 
#define  MGN_MCS1 157 
#define  MGN_MCS10 156 
#define  MGN_MCS10_SG 155 
#define  MGN_MCS11 154 
#define  MGN_MCS11_SG 153 
#define  MGN_MCS12 152 
#define  MGN_MCS12_SG 151 
#define  MGN_MCS13 150 
#define  MGN_MCS13_SG 149 
#define  MGN_MCS14 148 
#define  MGN_MCS14_SG 147 
#define  MGN_MCS15 146 
#define  MGN_MCS15_SG 145 
#define  MGN_MCS1_SG 144 
#define  MGN_MCS2 143 
#define  MGN_MCS2_SG 142 
#define  MGN_MCS3 141 
#define  MGN_MCS3_SG 140 
#define  MGN_MCS4 139 
#define  MGN_MCS4_SG 138 
#define  MGN_MCS5 137 
#define  MGN_MCS5_SG 136 
#define  MGN_MCS6 135 
#define  MGN_MCS6_SG 134 
#define  MGN_MCS7 133 
#define  MGN_MCS7_SG 132 
#define  MGN_MCS8 131 
#define  MGN_MCS8_SG 130 
#define  MGN_MCS9 129 
#define  MGN_MCS9_SG 128 

u8 MRateToHwRate8190Pci(u8 rate)
{
	u8	ret = DESC92S_RATE1M;

	switch(rate)
	{
		// CCK and OFDM non-HT rates
	case MGN_1M:		ret = DESC92S_RATE1M;	break;
	case MGN_2M:		ret = DESC92S_RATE2M;	break;
	case MGN_5_5M:		ret = DESC92S_RATE5_5M;	break;
	case MGN_11M:		ret = DESC92S_RATE11M;	break;
	case MGN_6M:		ret = DESC92S_RATE6M;	break;
	case MGN_9M:		ret = DESC92S_RATE9M;	break;
	case MGN_12M:		ret = DESC92S_RATE12M;	break;
	case MGN_18M:		ret = DESC92S_RATE18M;	break;
	case MGN_24M:		ret = DESC92S_RATE24M;	break;
	case MGN_36M:		ret = DESC92S_RATE36M;	break;
	case MGN_48M:		ret = DESC92S_RATE48M;	break;
	case MGN_54M:		ret = DESC92S_RATE54M;	break;

		// HT rates since here
	case MGN_MCS0:		ret = DESC92S_RATEMCS0;	break;
	case MGN_MCS1:		ret = DESC92S_RATEMCS1;	break;
	case MGN_MCS2:		ret = DESC92S_RATEMCS2;	break;
	case MGN_MCS3:		ret = DESC92S_RATEMCS3;	break;
	case MGN_MCS4:		ret = DESC92S_RATEMCS4;	break;
	case MGN_MCS5:		ret = DESC92S_RATEMCS5;	break;
	case MGN_MCS6:		ret = DESC92S_RATEMCS6;	break;
	case MGN_MCS7:		ret = DESC92S_RATEMCS7;	break;
	case MGN_MCS8:		ret = DESC92S_RATEMCS8;	break;
	case MGN_MCS9:		ret = DESC92S_RATEMCS9;	break;
	case MGN_MCS10:	ret = DESC92S_RATEMCS10;	break;
	case MGN_MCS11:	ret = DESC92S_RATEMCS11;	break;
	case MGN_MCS12:	ret = DESC92S_RATEMCS12;	break;
	case MGN_MCS13:	ret = DESC92S_RATEMCS13;	break;
	case MGN_MCS14:	ret = DESC92S_RATEMCS14;	break;
	case MGN_MCS15:	ret = DESC92S_RATEMCS15;	break;

	// Set the highest SG rate
	case MGN_MCS0_SG:
	case MGN_MCS1_SG:
	case MGN_MCS2_SG:
	case MGN_MCS3_SG:
	case MGN_MCS4_SG:
	case MGN_MCS5_SG:
	case MGN_MCS6_SG:
	case MGN_MCS7_SG:
	case MGN_MCS8_SG:
	case MGN_MCS9_SG:
	case MGN_MCS10_SG:
	case MGN_MCS11_SG:
	case MGN_MCS12_SG:
	case MGN_MCS13_SG:
	case MGN_MCS14_SG:
	case MGN_MCS15_SG:
	{
		ret = DESC92S_RATEMCS15_SG;
		break;
	}

	default:		break;
	}
	return ret;
}