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
typedef  scalar_t__ ushort ;
typedef  unsigned char uchar ;
typedef  int /*<<< orphan*/  PortAddr ;

/* Variables and functions */
 unsigned short AscGetChipLramData (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  AscSetChipLramAddr (int /*<<< orphan*/ ,scalar_t__) ; 
 scalar_t__ isodd_word (scalar_t__) ; 

__attribute__((used)) static uchar AscReadLramByte(PortAddr iop_base, ushort addr)
{
	unsigned char byte_data;
	unsigned short word_data;

	if (isodd_word(addr)) {
		AscSetChipLramAddr(iop_base, addr - 1);
		word_data = AscGetChipLramData(iop_base);
		byte_data = (word_data >> 8) & 0xFF;
	} else {
		AscSetChipLramAddr(iop_base, addr);
		word_data = AscGetChipLramData(iop_base);
		byte_data = word_data & 0xFF;
	}
	return byte_data;
}