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
struct node_t {scalar_t__ numbits; int bits; } ;
struct huffman_decoder {int numcodes; int maxbits; int /*<<< orphan*/ * lookup; struct node_t* huffnode; } ;
typedef  int /*<<< orphan*/  lookup_value ;

/* Variables and functions */
 int /*<<< orphan*/  MAKE_LOOKUP (int,scalar_t__) ; 

void huffman_build_lookup_table(struct huffman_decoder* decoder)
{
	/* iterate over all codes */
	int curcode;
	for (curcode = 0; curcode < decoder->numcodes; curcode++)
	{
		/* process all nodes which have non-zero bits */
		struct node_t* node = &decoder->huffnode[curcode];
		if (node->numbits > 0)
		{
         int shift;
         lookup_value *dest;
         lookup_value *destend;
			/* set up the entry */
			lookup_value value = MAKE_LOOKUP(curcode, node->numbits);

			/* fill all matching entries */
			shift = decoder->maxbits - node->numbits;
			dest = &decoder->lookup[node->bits << shift];
			destend = &decoder->lookup[((node->bits + 1) << shift) - 1];
			while (dest <= destend)
				*dest++ = value;
		}
	}
}