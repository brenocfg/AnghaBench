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
typedef  int uint32_t ;
struct bitstream {int bits; size_t doffset; size_t dlength; int buffer; int* read; } ;

/* Variables and functions */

uint32_t bitstream_peek(struct bitstream* bitstream, int numbits)
{
	if (numbits == 0)
		return 0;

	/* fetch data if we need more */
	if (numbits > bitstream->bits)
	{
		while (bitstream->bits <= 24)
		{
			if (bitstream->doffset < bitstream->dlength)
				bitstream->buffer |= bitstream->read[bitstream->doffset] << (24 - bitstream->bits);
			bitstream->doffset++;
			bitstream->bits += 8;
		}
	}

	/* return the data */
	return bitstream->buffer >> (32 - numbits);
}