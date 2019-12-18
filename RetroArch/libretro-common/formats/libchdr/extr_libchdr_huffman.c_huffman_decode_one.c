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
typedef  size_t uint32_t ;
struct huffman_decoder {int* lookup; int /*<<< orphan*/  maxbits; } ;
struct bitstream {int dummy; } ;
typedef  int lookup_value ;

/* Variables and functions */
 size_t bitstream_peek (struct bitstream*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bitstream_remove (struct bitstream*,int) ; 

uint32_t huffman_decode_one(struct huffman_decoder* decoder, struct bitstream* bitbuf)
{
	/* peek ahead to get maxbits worth of data */
	uint32_t bits = bitstream_peek(bitbuf, decoder->maxbits);

	/* look it up, then remove the actual number of bits for this code */
	lookup_value lookup = decoder->lookup[bits];
	bitstream_remove(bitbuf, lookup & 0x1f);

	/* return the value */
	return lookup >> 5;
}