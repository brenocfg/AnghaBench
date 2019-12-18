#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int brword ;
struct TYPE_6__ {int* buffer; scalar_t__ consumed_words; scalar_t__ words; scalar_t__ consumed_bits; } ;
typedef  unsigned int FLAC__uint32 ;
typedef  void* FLAC__byte ;
typedef  int FLAC__bool ;
typedef  TYPE_1__ FLAC__BitReader ;

/* Variables and functions */
 int /*<<< orphan*/  FLAC__ASSERT (int) ; 
 unsigned int FLAC__BYTES_PER_WORD ; 
 int FLAC__bitreader_is_consumed_byte_aligned (TYPE_1__*) ; 
 int /*<<< orphan*/  FLAC__bitreader_read_raw_uint32 (TYPE_1__*,unsigned int*,int) ; 
 int /*<<< orphan*/  bitreader_read_from_client_ (TYPE_1__*) ; 

FLAC__bool FLAC__bitreader_read_byte_block_aligned_no_crc(FLAC__BitReader *br, FLAC__byte *val, unsigned nvals)
{
	FLAC__uint32 x;

	FLAC__ASSERT(0 != br);
	FLAC__ASSERT(0 != br->buffer);
	FLAC__ASSERT(FLAC__bitreader_is_consumed_byte_aligned(br));

	/* step 1: read from partial head word to get word aligned */
	while(nvals && br->consumed_bits) { /* i.e. run until we read 'nvals' bytes or we hit the end of the head word */
		if(!FLAC__bitreader_read_raw_uint32(br, &x, 8))
			return false;
		*val++ = (FLAC__byte)x;
		nvals--;
	}
	if(0 == nvals)
		return true;
	/* step 2: read whole words in chunks */
	while(nvals >= FLAC__BYTES_PER_WORD) {
		if(br->consumed_words < br->words) {
			const brword word = br->buffer[br->consumed_words++];
#if FLAC__BYTES_PER_WORD == 4
			val[0] = (FLAC__byte)(word >> 24);
			val[1] = (FLAC__byte)(word >> 16);
			val[2] = (FLAC__byte)(word >> 8);
			val[3] = (FLAC__byte)word;
#elif FLAC__BYTES_PER_WORD == 8
			val[0] = (FLAC__byte)(word >> 56);
			val[1] = (FLAC__byte)(word >> 48);
			val[2] = (FLAC__byte)(word >> 40);
			val[3] = (FLAC__byte)(word >> 32);
			val[4] = (FLAC__byte)(word >> 24);
			val[5] = (FLAC__byte)(word >> 16);
			val[6] = (FLAC__byte)(word >> 8);
			val[7] = (FLAC__byte)word;
#else
			for(x = 0; x < FLAC__BYTES_PER_WORD; x++)
				val[x] = (FLAC__byte)(word >> (8*(FLAC__BYTES_PER_WORD-x-1)));
#endif
			val += FLAC__BYTES_PER_WORD;
			nvals -= FLAC__BYTES_PER_WORD;
		}
		else if(!bitreader_read_from_client_(br))
			return false;
	}
	/* step 3: read any remainder from partial tail bytes */
	while(nvals) {
		if(!FLAC__bitreader_read_raw_uint32(br, &x, 8))
			return false;
		*val++ = (FLAC__byte)x;
		nvals--;
	}

	return true;
}