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
struct huffman_decoder {struct huffman_decoder* huffnode; struct huffman_decoder* lookup; } ;

/* Variables and functions */
 int /*<<< orphan*/  free (struct huffman_decoder*) ; 

void delete_huffman_decoder(struct huffman_decoder* decoder)
{
	if (decoder != NULL)
	{
		if (decoder->lookup != NULL)
			free(decoder->lookup);
		if (decoder->huffnode != NULL)
			free(decoder->huffnode);
		free(decoder);
	}
}