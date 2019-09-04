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

unsigned long HashString(const char *lpszkeyName, unsigned long dwHashType )  
{  
	unsigned char *key  = (unsigned char *)lpszkeyName;  
	unsigned long seed1 = 0x7FED7FED;  
	unsigned long seed2 = 0xEEEEEEEE;  
	int ch;  

	while( *key != 0 )  
	{  
		ch = *key++;  
		seed1 = cryptTable[(dwHashType<<8) + ch] ^ (seed1 + seed2);  
		seed2 = ch + seed1 + seed2 + (seed2<<5) + 3;  
	}  
	return seed1;  
}