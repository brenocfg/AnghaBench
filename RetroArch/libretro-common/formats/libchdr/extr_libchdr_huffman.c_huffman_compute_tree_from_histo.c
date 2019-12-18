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
struct huffman_decoder {int numcodes; int maxbits; scalar_t__* datahisto; } ;
typedef  enum huffman_error { ____Placeholder_huffman_error } huffman_error ;

/* Variables and functions */
 int huffman_assign_canonical_codes (struct huffman_decoder*) ; 
 int huffman_build_tree (struct huffman_decoder*,int,int) ; 

enum huffman_error huffman_compute_tree_from_histo(struct huffman_decoder* decoder)
{
	/* compute the number of data items in the histogram */
	int i;
   uint32_t upperweight;
	uint32_t lowerweight = 0;
	uint32_t sdatacount = 0;
	for (i = 0; i < decoder->numcodes; i++)
		sdatacount += decoder->datahisto[i];

	/* binary search to achieve the optimum encoding */
	upperweight = sdatacount * 2;
	while (1)
	{
		/* build a tree using the current weight */
		uint32_t curweight = (upperweight + lowerweight) / 2;
		int curmaxbits = huffman_build_tree(decoder, sdatacount, curweight);

		/* apply binary search here */
		if (curmaxbits <= decoder->maxbits)
		{
			lowerweight = curweight;

			/* early out if it worked with the raw weights, or if we're done searching */
			if (curweight == sdatacount || (upperweight - lowerweight) <= 1)
				break;
		}
		else
			upperweight = curweight;
	}

	/* assign canonical codes for all nodes based on their code lengths */
	return huffman_assign_canonical_codes(decoder);
}