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

/* Variables and functions */
 unsigned long* cryptTable ; 

void prepareCryptTable()  
{  
	unsigned long seed = 0x00100001, index1 = 0, index2 = 0, i;  

	for( index1 = 0; index1 <0x100; index1++ )  
	{  
		for( index2 = index1, i = 0; i < 5; i++, index2 += 0x100)  
		{  
			unsigned long temp1, temp2;  
			seed = (seed * 125 + 3) % 0x2AAAAB;  
			temp1 = (seed & 0xFFFF)<<0x10;  
			seed = (seed * 125 + 3) % 0x2AAAAB;  
			temp2 = (seed & 0xFFFF);  
			cryptTable[index2] = ( temp1 | temp2 );  
		}  
	}  
}