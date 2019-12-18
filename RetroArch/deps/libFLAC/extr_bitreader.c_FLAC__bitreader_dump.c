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
typedef  unsigned int brword ;
struct TYPE_3__ {int capacity; int words; int bytes; int consumed_words; int consumed_bits; unsigned int* buffer; } ;
typedef  TYPE_1__ FLAC__BitReader ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 unsigned int FLAC__BITS_PER_WORD ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ *,char*,...) ; 

void FLAC__bitreader_dump(const FLAC__BitReader *br, FILE *out)
{
	unsigned i, j;
	if(br == 0) {
		fprintf(out, "bitreader is NULL\n");
	}
	else {
		fprintf(out, "bitreader: capacity=%u words=%u bytes=%u consumed: words=%u, bits=%u\n", br->capacity, br->words, br->bytes, br->consumed_words, br->consumed_bits);

		for(i = 0; i < br->words; i++) {
			fprintf(out, "%08X: ", i);
			for(j = 0; j < FLAC__BITS_PER_WORD; j++)
				if(i < br->consumed_words || (i == br->consumed_words && j < br->consumed_bits))
					fprintf(out, ".");
				else
					fprintf(out, "%01u", br->buffer[i] & ((brword)1 << (FLAC__BITS_PER_WORD-j-1)) ? 1:0);
			fprintf(out, "\n");
		}
		if(br->bytes > 0) {
			fprintf(out, "%08X: ", i);
			for(j = 0; j < br->bytes*8; j++)
				if(i < br->consumed_words || (i == br->consumed_words && j < br->consumed_bits))
					fprintf(out, ".");
				else
					fprintf(out, "%01u", br->buffer[i] & ((brword)1 << (br->bytes*8-j-1)) ? 1:0);
			fprintf(out, "\n");
		}
	}
}