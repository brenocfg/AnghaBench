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
struct hw_data {int dummy; } ;
typedef  int /*<<< orphan*/  ChanInfo ;

/* Variables and functions */
 int /*<<< orphan*/  RFSynthesizer_SetPowerIndex (struct hw_data*,int) ; 

void set_tx_power_per_channel_max2829(  struct hw_data * pHwData,  ChanInfo Channel)
{
	RFSynthesizer_SetPowerIndex( pHwData, 100 ); // 20060620.1 Modify
}