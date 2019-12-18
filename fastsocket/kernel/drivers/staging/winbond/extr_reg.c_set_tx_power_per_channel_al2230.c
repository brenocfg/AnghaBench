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
struct TYPE_3__ {int ChanNo; } ;
typedef  TYPE_1__ ChanInfo ;

/* Variables and functions */
 int /*<<< orphan*/  RFSynthesizer_SetPowerIndex (struct hw_data*,int) ; 

void set_tx_power_per_channel_al2230(  struct hw_data * pHwData,  ChanInfo Channel )
{
	u8	index = 100;

	if (pHwData->TxVgaFor24[Channel.ChanNo - 1] != 0xff) // 20060620.1 Add
		index = pHwData->TxVgaFor24[Channel.ChanNo - 1];

	RFSynthesizer_SetPowerIndex( pHwData, index );
}