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
typedef  int u32 ;

/* Variables and functions */
 int CardComputeCrc (int*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ETH_ALEN ; 

void CardGetMulticastBit( u8 Address[ETH_ALEN], u8 *Byte, u8 *Value )
{
    u32 Crc;
    u32 BitNumber;

    // First compute the CRC.
    Crc = CardComputeCrc(Address, ETH_ALEN);

	// The computed CRC is bit0~31 from left to right
	//At first we should do right shift 25bits, and read 7bits by using '&', 2^7=128
	BitNumber = (u32) ((Crc >> 26) & 0x3f);

	*Byte  = (u8) (BitNumber >> 3);// 900514 original (BitNumber / 8)
	*Value = (u8) ((u8)1 << (BitNumber % 8));
}