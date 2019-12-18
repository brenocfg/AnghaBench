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
 int BIT0 ; 
 int BIT1 ; 
 int BIT2 ; 
 int BIT3 ; 

__attribute__((used)) static	void
efuse_WordEnableDataRead(	u8 word_en,u8 *sourdata,u8 *targetdata)
{
	//u8 tmpindex = 0;

	//DbgPrint("efuse_WordEnableDataRead word_en = %x\n", word_en);

	//RT_PRINT_DATA(COMP_EFUSE, DBG_LOUD, ("sourdata\n"), sourdata, 8);
	//RT_PRINT_DATA(COMP_EFUSE, DBG_LOUD, ("targetdata\n"), targetdata, 8);

	if (!(word_en&BIT0))
	{
		targetdata[0] = sourdata[0];//sourdata[tmpindex++];
		targetdata[1] = sourdata[1];//sourdata[tmpindex++];
	}
	if (!(word_en&BIT1))
	{
		targetdata[2] = sourdata[2];//sourdata[tmpindex++];
		targetdata[3] = sourdata[3];//sourdata[tmpindex++];
	}
	if (!(word_en&BIT2))
	{
		targetdata[4] = sourdata[4];//sourdata[tmpindex++];
		targetdata[5] = sourdata[5];//sourdata[tmpindex++];
	}
	if (!(word_en&BIT3))
	{
		targetdata[6] = sourdata[6];//sourdata[tmpindex++];
		targetdata[7] = sourdata[7];//sourdata[tmpindex++];
	}
}