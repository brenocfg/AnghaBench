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
typedef  int UBYTE ;
struct TYPE_3__ {int type; int size; int* image; } ;
typedef  TYPE_1__ CARTRIDGE_image_t ;

/* Variables and functions */
#define  CARTRIDGE_ATRAX_SDX_128 129 
#define  CARTRIDGE_ATRAX_SDX_64 128 
 scalar_t__ Util_malloc (unsigned int const) ; 
 int /*<<< orphan*/  free (int*) ; 

__attribute__((used)) static void PreprocessCart(CARTRIDGE_image_t *cart)
{
	switch (cart->type) {
	case CARTRIDGE_ATRAX_SDX_64:
	case CARTRIDGE_ATRAX_SDX_128: {
		/* The address lines are connected a follows:
		   (left - cartridge port + bank select, right - EPROM)
		    A0 -  A6
		    A1 -  A7
		    A2 - A12
		    A3 - A15
		    A4 - A14
		    A5 - A13
		    A6 -  A8
		    A7 -  A5
		    A8 -  A4
		    A9 -  A3
		   A10 -  A0
		   A11 -  A1
		   A12 -  A2
		   A13 -  A9
		   A14 - A11
		   A15 - A10
		   A16 - A16 (only on ATRAX_SDX_128)

		    The data lines are connected as follows:
		    (left - cartridge port, right - EPROM)
		    D1 - Q0
		    D3 - Q1
		    D7 - Q2
		    D6 - Q3
		    D0 - Q4
		    D2 - Q5
		    D5 - Q6
		    D4 - Q7
		 */
		unsigned int i;
		unsigned int const size = cart->size << 10;
		UBYTE *new_image = (UBYTE *) Util_malloc(size);
		/* FIXME: Can be optimised by caching the results in a conversion
		   table, but doesn't seem to be worth it. */
		for (i = 0; i < size; i++) {
			unsigned int const rom_addr =
				(i &  0x0001 ?  0x0040 : 0) |
				(i &  0x0002 ?  0x0080 : 0) |
				(i &  0x0004 ?  0x1000 : 0) |
				(i &  0x0008 ?  0x8000 : 0) |
				(i &  0x0010 ?  0x4000 : 0) |
				(i &  0x0020 ?  0x2000 : 0) |
				(i &  0x0040 ?  0x0100 : 0) |
				(i &  0x0080 ?  0x0020 : 0) |
				(i &  0x0100 ?  0x0010 : 0) |
				(i &  0x0200 ?  0x0008 : 0) |
				(i &  0x0400 ?  0x0001 : 0) |
				(i &  0x0800 ?  0x0002 : 0) |
				(i &  0x1000 ?  0x0004 : 0) |
				(i &  0x2000 ?  0x0200 : 0) |
				(i &  0x4000 ?  0x0800 : 0) |
				(i &  0x8000 ?  0x0400 : 0) |
				(i & 0x10000 ? 0x10000 : 0);

			UBYTE byte = cart->image[rom_addr];
			new_image[i] =
					(byte & 0x01 ? 0x02 : 0) |
					(byte & 0x02 ? 0x08 : 0) |
					(byte & 0x04 ? 0x80 : 0) |
					(byte & 0x08 ? 0x40 : 0) |
					(byte & 0x10 ? 0x01 : 0) |
					(byte & 0x20 ? 0x04 : 0) |
					(byte & 0x40 ? 0x20 : 0) |
					(byte & 0x80 ? 0x10 : 0);
		}
		free(cart->image);
		cart->image = new_image;
		break;
	}
	}
}