#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int u8 ;
struct hw_data {int* TxVgaFor24; TYPE_1__* TxVgaFor50; } ;
struct TYPE_5__ {int band; int /*<<< orphan*/  ChanNo; } ;
struct TYPE_4__ {int TxVgaValue; int /*<<< orphan*/  ChanNo; } ;
typedef  TYPE_2__ ChanInfo ;

/* Variables and functions */
#define  BAND_TYPE_DSSS 130 
#define  BAND_TYPE_OFDM_24 129 
#define  BAND_TYPE_OFDM_5 128 
 int /*<<< orphan*/  RFSynthesizer_SetPowerIndex (struct hw_data*,int) ; 

void set_tx_power_per_channel_al7230(  struct hw_data * pHwData,  ChanInfo Channel)
{
	u8	i, index = 100;

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
			{
				for (i =0; i<35; i++)
				{
					if (Channel.ChanNo == pHwData->TxVgaFor50[i].ChanNo)
					{
						if (pHwData->TxVgaFor50[i].TxVgaValue != 0xff)
							index = pHwData->TxVgaFor50[i].TxVgaValue;
						break;
					}
				}
			}
			break;
	}
	RFSynthesizer_SetPowerIndex( pHwData, index );
}