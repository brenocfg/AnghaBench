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
struct huffman_decoder {int maxbits; int numcodes; TYPE_1__* huffnode; } ;
struct bitstream {int dummy; } ;
typedef  enum huffman_error { ____Placeholder_huffman_error } huffman_error ;
struct TYPE_2__ {int numbits; } ;

/* Variables and functions */
 int HUFFERR_INPUT_BUFFER_TOO_SMALL ; 
 int HUFFERR_INVALID_DATA ; 
 int HUFFERR_NONE ; 
 scalar_t__ bitstream_overflow (struct bitstream*) ; 
 int bitstream_read (struct bitstream*,int) ; 
 int huffman_assign_canonical_codes (struct huffman_decoder*) ; 
 int /*<<< orphan*/  huffman_build_lookup_table (struct huffman_decoder*) ; 

enum huffman_error huffman_import_tree_rle(struct huffman_decoder* decoder, struct bitstream* bitbuf)
{
   enum huffman_error error;
	/* bits per entry depends on the maxbits */
	int numbits;
	int curnode;
	if (decoder->maxbits >= 16)
		numbits = 5;
	else if (decoder->maxbits >= 8)
		numbits = 4;
	else
		numbits = 3;

	/* loop until we read all the nodes */
	for (curnode = 0; curnode < decoder->numcodes; )
	{
		/* a non-one value is just raw */
		int nodebits = bitstream_read(bitbuf, numbits);
		if (nodebits != 1)
			decoder->huffnode[curnode++].numbits = nodebits;

		/* a one value is an escape code */
		else
		{
			/* a double 1 is just a single 1 */
			nodebits = bitstream_read(bitbuf, numbits);
			if (nodebits == 1)
				decoder->huffnode[curnode++].numbits = nodebits;

			/* otherwise, we need one for value for the repeat count */
			else
			{
				int repcount = bitstream_read(bitbuf, numbits) + 3;
				while (repcount--)
					decoder->huffnode[curnode++].numbits = nodebits;
			}
		}
	}

	/* make sure we ended up with the right number */
	if (curnode != decoder->numcodes)
		return HUFFERR_INVALID_DATA;

	/* assign canonical codes for all nodes based on their code lengths */
	error = huffman_assign_canonical_codes(decoder);
	if (error != HUFFERR_NONE)
		return error;

	/* build the lookup table */
	huffman_build_lookup_table(decoder);

	/* determine final input length and report errors */
	return bitstream_overflow(bitbuf) ? HUFFERR_INPUT_BUFFER_TOO_SMALL : HUFFERR_NONE;
}