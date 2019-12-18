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
typedef  char u8 ;
typedef  int u32 ;
struct hw_data {int* phy_para; } ;

/* Variables and functions */
 int* al7230_rf_data_50 ; 

void Set_ChanIndep_RfData_al7230_50(  struct hw_data * pHwData, u32 *pltmp, char number)
{
	u8	i;

	for( i=0; i<number; i++ )
	{
		pHwData->phy_para[i] = al7230_rf_data_50[i];
		pltmp[i] = (1 << 31) | (0 << 30) | (24 << 24) | (al7230_rf_data_50[i]&0xffffff);
	}
}