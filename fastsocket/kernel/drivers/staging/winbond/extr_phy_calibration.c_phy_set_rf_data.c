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
typedef  int u32 ;
struct hw_data {int phy_type; } ;

/* Variables and functions */
 int BitReverse (int,int) ; 
#define  RF_AIROHA_2230 137 
#define  RF_AIROHA_2230S 136 
#define  RF_AIROHA_7230 135 
#define  RF_MAXIM_2825 134 
#define  RF_MAXIM_2827 133 
#define  RF_MAXIM_2828 132 
#define  RF_MAXIM_2829 131 
#define  RF_MAXIM_V1 130 
#define  RF_WB_242 129 
#define  RF_WB_242_1 128 
 int /*<<< orphan*/  Wb35Reg_WriteSync (struct hw_data*,int,int) ; 

void phy_set_rf_data(  struct hw_data * pHwData,  u32 index,  u32 value )
{
   u32 ltmp=0;

    switch( pHwData->phy_type )
	{
		case RF_MAXIM_2825:
		case RF_MAXIM_V1: // 11g Winbond 2nd BB(with Phy board (v1) + Maxim 331)
			ltmp = (1 << 31) | (0 << 30) | (18 << 24) | BitReverse( value, 18 );
			break;

		case RF_MAXIM_2827:
			ltmp = (1 << 31) | (0 << 30) | (18 << 24) | BitReverse( value, 18 );
			break;

		case RF_MAXIM_2828:
			ltmp = (1 << 31) | (0 << 30) | (18 << 24) | BitReverse( value, 18 );
			break;

		case RF_MAXIM_2829:
			ltmp = (1 << 31) | (0 << 30) | (18 << 24) | BitReverse( value, 18 );
			break;

		case RF_AIROHA_2230:
		case RF_AIROHA_2230S: // 20060420 Add this
			ltmp = (1 << 31) | (0 << 30) | (20 << 24) | BitReverse( value, 20 );
			break;

		case RF_AIROHA_7230:
			ltmp = (1 << 31) | (0 << 30) | (24 << 24) | (value&0xffffff);
			break;

		case RF_WB_242:
		case RF_WB_242_1: // 20060619.5 Add
			ltmp = (1 << 31) | (0 << 30) | (24 << 24) | BitReverse( value, 24 );
			break;
	}

	Wb35Reg_WriteSync( pHwData, 0x0864, ltmp );
}