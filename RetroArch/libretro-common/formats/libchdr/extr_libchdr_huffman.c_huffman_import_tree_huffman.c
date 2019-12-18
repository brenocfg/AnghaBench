#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int uint8_t ;
typedef  int uint32_t ;
struct huffman_decoder {int numcodes; TYPE_1__* huffnode; } ;
struct bitstream {int dummy; } ;
typedef  enum huffman_error { ____Placeholder_huffman_error } huffman_error ;
struct TYPE_2__ {int numbits; } ;

/* Variables and functions */
 int HUFFERR_INPUT_BUFFER_TOO_SMALL ; 
 int HUFFERR_INVALID_DATA ; 
 int HUFFERR_NONE ; 
 scalar_t__ bitstream_overflow (struct bitstream*) ; 
 void* bitstream_read (struct bitstream*,int) ; 
 struct huffman_decoder* create_huffman_decoder (int,int) ; 
 int /*<<< orphan*/  delete_huffman_decoder (struct huffman_decoder*) ; 
 int huffman_assign_canonical_codes (struct huffman_decoder*) ; 
 int /*<<< orphan*/  huffman_build_lookup_table (struct huffman_decoder*) ; 
 int huffman_decode_one (struct huffman_decoder*,struct bitstream*) ; 

enum huffman_error huffman_import_tree_huffman(struct huffman_decoder* decoder, struct bitstream* bitbuf)
{
	int last = 0;
	int curcode;
   uint32_t temp;
   enum huffman_error error;
	uint8_t rlefullbits = 0;
	int index, count = 0;
   int start;
	/* start by parsing the lengths for the small tree */
	struct huffman_decoder* smallhuff = create_huffman_decoder(24, 6);

	smallhuff->huffnode[0].numbits = bitstream_read(bitbuf, 3);
	start = bitstream_read(bitbuf, 3) + 1;

	for (index = 1; index < 24; index++)
	{
		if (index < start || count == 7)
			smallhuff->huffnode[index].numbits = 0;
		else
		{
			count = bitstream_read(bitbuf, 3);
			smallhuff->huffnode[index].numbits = (count == 7) ? 0 : count;
		}
	}

	/* then regenerate the tree */
	error = huffman_assign_canonical_codes(smallhuff);
	if (error != HUFFERR_NONE)
		return error;
	huffman_build_lookup_table(smallhuff);

	/* determine the maximum length of an RLE count */
	temp = decoder->numcodes - 9;
	while (temp != 0)
    {
        temp >>= 1;
        rlefullbits++;
    }

	/* now process the rest of the data */
	for (curcode = 0; curcode < decoder->numcodes; )
	{
		int value = huffman_decode_one(smallhuff, bitbuf);
		if (value != 0)
			decoder->huffnode[curcode++].numbits = last = value - 1;
		else
		{
			int count = bitstream_read(bitbuf, 3) + 2;
			if (count == 7+2)
				count += bitstream_read(bitbuf, rlefullbits);
			for ( ; count != 0 && curcode < decoder->numcodes; count--)
				decoder->huffnode[curcode++].numbits = last;
		}
	}

	/* make sure we ended up with the right number */
	if (curcode != decoder->numcodes)
   {
      delete_huffman_decoder(smallhuff);
		return HUFFERR_INVALID_DATA;
   }

	/* assign canonical codes for all nodes based on their code lengths */
	error = huffman_assign_canonical_codes(decoder);
	if (error != HUFFERR_NONE)
   {
      delete_huffman_decoder(smallhuff);
		return error;
   }

	/* build the lookup table */
	huffman_build_lookup_table(decoder);
	delete_huffman_decoder(smallhuff);

	/* determine final input length and report errors */
	return bitstream_overflow(bitbuf) ? HUFFERR_INPUT_BUFFER_TOO_SMALL : HUFFERR_NONE;
}