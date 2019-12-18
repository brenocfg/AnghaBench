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
struct node_t {int dummy; } ;
struct huffman_decoder {int numcodes; int maxbits; scalar_t__ rleremaining; scalar_t__ prevdata; int /*<<< orphan*/ * datahisto; struct node_t* huffnode; int /*<<< orphan*/ * lookup; } ;
typedef  int /*<<< orphan*/  lookup_value ;

/* Variables and functions */
 scalar_t__ malloc (int) ; 

struct huffman_decoder* create_huffman_decoder(int numcodes, int maxbits)
{
   struct huffman_decoder* decoder;
	/* limit to 24 bits */
	if (maxbits > 24)
		return NULL;

	decoder = (struct huffman_decoder*)malloc(sizeof(struct huffman_decoder));
	decoder->numcodes = numcodes;
	decoder->maxbits = maxbits;
	decoder->lookup = (lookup_value*)malloc(sizeof(lookup_value) * (1 << maxbits));
	decoder->huffnode = (struct node_t*)malloc(sizeof(struct node_t) * numcodes);
	decoder->datahisto = NULL;
	decoder->prevdata = 0;
	decoder->rleremaining = 0;
	return decoder;
}