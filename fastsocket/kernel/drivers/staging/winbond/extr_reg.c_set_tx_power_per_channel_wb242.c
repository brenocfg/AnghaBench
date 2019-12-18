#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int u8 ;
struct hw_data {int* TxVgaFor24; } ;
struct TYPE_3__ {int band; int /*<<< orphan*/  ChanNo; } ;
typedef  TYPE_1__ ChanInfo ;

/* Variables and functions */
#define  BAND_TYPE_DSSS 130 
#define  BAND_TYPE_OFDM_24 129 
#define  BAND_TYPE_OFDM_5 128 
 int /*<<< orphan*/  RFSynthesizer_SetPowerIndex (struct hw_data*,int) ; 

void set_tx_power_per_channel_wb242(  struct hw_data * pHwData,  ChanInfo Channel)
{
	u8	index = 100;

	switch ( Channel.band )
	{
		case BAND_TYPE_DSSS:
		case BAND_TYPE_OFDM_24:
			{
				if (pHwData->TxVgaFor24[Channel.ChanNo - 1] != 0xff)
					index = pHwData->TxVgaFor24[Channel.ChanNo - 1];
			}
			break;
		case BAND_TYPE_OFDM_5:
			break;
	}
	RFSynthesizer_SetPowerIndex( pHwData, index );
}