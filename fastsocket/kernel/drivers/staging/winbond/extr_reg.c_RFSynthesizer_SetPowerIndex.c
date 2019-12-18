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
typedef  scalar_t__ u32 ;
struct hw_data {scalar_t__ band; size_t power_index; scalar_t__ phy_type; } ;

/* Variables and functions */
 scalar_t__ BAND_TYPE_OFDM_24 ; 
 size_t RFSynthesizer_SetAiroha2230Power (struct hw_data*,size_t) ; 
 size_t RFSynthesizer_SetAiroha7230Power (struct hw_data*,size_t) ; 
 size_t RFSynthesizer_SetMaxim2825Power (struct hw_data*,size_t) ; 
 size_t RFSynthesizer_SetMaxim2827_24Power (struct hw_data*,size_t) ; 
 size_t RFSynthesizer_SetMaxim2827_50Power (struct hw_data*,size_t) ; 
 size_t RFSynthesizer_SetMaxim2828_24Power (struct hw_data*,size_t) ; 
 size_t RFSynthesizer_SetMaxim2828_50Power (struct hw_data*,size_t) ; 
 size_t RFSynthesizer_SetWinbond242Power (struct hw_data*,size_t) ; 
 scalar_t__ RF_AIROHA_2230 ; 
 scalar_t__ RF_AIROHA_2230S ; 
 scalar_t__ RF_AIROHA_7230 ; 
 scalar_t__ RF_MAXIM_2825 ; 
 scalar_t__ RF_MAXIM_2827 ; 
 scalar_t__ RF_MAXIM_2828 ; 
 scalar_t__ RF_WB_242 ; 
 scalar_t__ RF_WB_242_1 ; 
 scalar_t__** al2230_txvga_data ; 
 scalar_t__** al7230_txvga_data ; 
 scalar_t__** w89rf242_txvga_data ; 

u8 RFSynthesizer_SetPowerIndex(  struct hw_data * pHwData,  u8 PowerIndex )
{
	u32	Band = pHwData->band;
	u8	index=0;

	if( pHwData->power_index == PowerIndex ) // 20060620.1 Add
		return PowerIndex;

	if (RF_MAXIM_2825 == pHwData->phy_type)
	{
		// Channel 1 - 13
		index = RFSynthesizer_SetMaxim2825Power( pHwData, PowerIndex );
	}
	else if (RF_MAXIM_2827 == pHwData->phy_type)
	{
		if( Band <= BAND_TYPE_OFDM_24 )    // Channel 1 - 13
			index = RFSynthesizer_SetMaxim2827_24Power( pHwData, PowerIndex );
		else// if( Band == BAND_TYPE_OFDM_5 )  // Channel 36 - 64
			index = RFSynthesizer_SetMaxim2827_50Power( pHwData, PowerIndex );
	}
	else if (RF_MAXIM_2828 == pHwData->phy_type)
	{
		if( Band <= BAND_TYPE_OFDM_24 )    // Channel 1 - 13
			index = RFSynthesizer_SetMaxim2828_24Power( pHwData, PowerIndex );
		else// if( Band == BAND_TYPE_OFDM_5 )  // Channel 36 - 64
			index = RFSynthesizer_SetMaxim2828_50Power( pHwData, PowerIndex );
	}
	else if( RF_AIROHA_2230 == pHwData->phy_type )
	{
		//Power index: 0 ~ 63 // Channel 1 - 14
		index = RFSynthesizer_SetAiroha2230Power( pHwData, PowerIndex );
		index = (u8)al2230_txvga_data[index][1];
	}
	else if( RF_AIROHA_2230S == pHwData->phy_type ) // 20060420 Add this
	{
		//Power index: 0 ~ 63 // Channel 1 - 14
		index = RFSynthesizer_SetAiroha2230Power( pHwData, PowerIndex );
		index = (u8)al2230_txvga_data[index][1];
	}
	else if( RF_AIROHA_7230 == pHwData->phy_type )
	{
		//Power index: 0 ~ 63
		index = RFSynthesizer_SetAiroha7230Power( pHwData, PowerIndex );
		index = (u8)al7230_txvga_data[index][1];
	}
	else if( (RF_WB_242 == pHwData->phy_type) ||
		 (RF_WB_242_1 == pHwData->phy_type) ) // 20060619.5 Add
	{
		//Power index: 0 ~ 19 for original. New range is 0 ~ 33
		index = RFSynthesizer_SetWinbond242Power( pHwData, PowerIndex );
		index = (u8)w89rf242_txvga_data[index][1];
	}

	pHwData->power_index = index;  // Backup current
	return index;
}