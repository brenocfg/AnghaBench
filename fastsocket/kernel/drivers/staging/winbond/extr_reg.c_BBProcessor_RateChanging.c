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
struct wb35_reg {void* BB48; void* BB4C; } ;
struct hw_data {int phy_type; struct wb35_reg reg; } ;

/* Variables and functions */
 void* BB48_DEFAULT_AL2230_11B ; 
 void* BB48_DEFAULT_AL2230_11G ; 
 void* BB48_DEFAULT_WB242_11B ; 
 void* BB48_DEFAULT_WB242_11G ; 
 void* BB4C_DEFAULT_AL2230_11B ; 
 void* BB4C_DEFAULT_AL2230_11G ; 
 void* BB4C_DEFAULT_WB242_11B ; 
 void* BB4C_DEFAULT_WB242_11G ; 
#define  RF_AIROHA_2230 130 
#define  RF_AIROHA_2230S 129 
#define  RF_WB_242 128 
 int /*<<< orphan*/  Wb35Reg_Write (struct hw_data*,int,void*) ; 

void BBProcessor_RateChanging(  struct hw_data * pHwData,  u8 rate ) // 20060613.1
{
	struct wb35_reg *reg = &pHwData->reg;
	unsigned char		Is11bRate;

	Is11bRate = (rate % 6) ? 1 : 0;
	switch( pHwData->phy_type )
	{
		case RF_AIROHA_2230:
		case RF_AIROHA_2230S: // 20060420 Add this
			if( Is11bRate )
			{
				if( (reg->BB48 != BB48_DEFAULT_AL2230_11B) &&
					(reg->BB4C != BB4C_DEFAULT_AL2230_11B) )
				{
					Wb35Reg_Write( pHwData, 0x1048, BB48_DEFAULT_AL2230_11B );
					Wb35Reg_Write( pHwData, 0x104c, BB4C_DEFAULT_AL2230_11B );
				}
			}
			else
			{
				if( (reg->BB48 != BB48_DEFAULT_AL2230_11G) &&
					(reg->BB4C != BB4C_DEFAULT_AL2230_11G) )
				{
					Wb35Reg_Write( pHwData, 0x1048, BB48_DEFAULT_AL2230_11G );
					Wb35Reg_Write( pHwData, 0x104c, BB4C_DEFAULT_AL2230_11G );
				}
			}
			break;

		case RF_WB_242: // 20060623 The fix only for old TxVGA setting
			if( Is11bRate )
			{
				if( (reg->BB48 != BB48_DEFAULT_WB242_11B) &&
					(reg->BB4C != BB4C_DEFAULT_WB242_11B) )
				{
					reg->BB48 = BB48_DEFAULT_WB242_11B;
					reg->BB4C = BB4C_DEFAULT_WB242_11B;
					Wb35Reg_Write( pHwData, 0x1048, BB48_DEFAULT_WB242_11B );
					Wb35Reg_Write( pHwData, 0x104c, BB4C_DEFAULT_WB242_11B );
				}
			}
			else
			{
				if( (reg->BB48 != BB48_DEFAULT_WB242_11G) &&
					(reg->BB4C != BB4C_DEFAULT_WB242_11G) )
				{
					reg->BB48 = BB48_DEFAULT_WB242_11G;
					reg->BB4C = BB4C_DEFAULT_WB242_11G;
					Wb35Reg_Write( pHwData, 0x1048, BB48_DEFAULT_WB242_11G );
					Wb35Reg_Write( pHwData, 0x104c, BB4C_DEFAULT_WB242_11G );
				}
			}
			break;
	}
}