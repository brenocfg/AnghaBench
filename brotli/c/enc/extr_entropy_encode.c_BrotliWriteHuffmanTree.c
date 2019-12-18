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
typedef  scalar_t__ uint8_t ;
typedef  scalar_t__ BROTLI_BOOL ;

/* Variables and functions */
 scalar_t__ BROTLI_FALSE ; 
 scalar_t__ BROTLI_INITIAL_REPEATED_CODE_LENGTH ; 
 int /*<<< orphan*/  BrotliWriteHuffmanTreeRepetitions (scalar_t__,scalar_t__ const,size_t,size_t*,scalar_t__*,scalar_t__*) ; 
 int /*<<< orphan*/  BrotliWriteHuffmanTreeRepetitionsZeros (size_t,size_t*,scalar_t__*,scalar_t__*) ; 
 int /*<<< orphan*/  DecideOverRleUse (scalar_t__ const*,size_t,scalar_t__*,scalar_t__*) ; 

void BrotliWriteHuffmanTree(const uint8_t* depth,
                            size_t length,
                            size_t* tree_size,
                            uint8_t* tree,
                            uint8_t* extra_bits_data) {
  uint8_t previous_value = BROTLI_INITIAL_REPEATED_CODE_LENGTH;
  size_t i;
  BROTLI_BOOL use_rle_for_non_zero = BROTLI_FALSE;
  BROTLI_BOOL use_rle_for_zero = BROTLI_FALSE;

  /* Throw away trailing zeros. */
  size_t new_length = length;
  for (i = 0; i < length; ++i) {
    if (depth[length - i - 1] == 0) {
      --new_length;
    } else {
      break;
    }
  }

  /* First gather statistics on if it is a good idea to do RLE. */
  if (length > 50) {
    /* Find RLE coding for longer codes.
       Shorter codes seem not to benefit from RLE. */
    DecideOverRleUse(depth, new_length,
                     &use_rle_for_non_zero, &use_rle_for_zero);
  }

  /* Actual RLE coding. */
  for (i = 0; i < new_length;) {
    const uint8_t value = depth[i];
    size_t reps = 1;
    if ((value != 0 && use_rle_for_non_zero) ||
        (value == 0 && use_rle_for_zero)) {
      size_t k;
      for (k = i + 1; k < new_length && depth[k] == value; ++k) {
        ++reps;
      }
    }
    if (value == 0) {
      BrotliWriteHuffmanTreeRepetitionsZeros(
          reps, tree_size, tree, extra_bits_data);
    } else {
      BrotliWriteHuffmanTreeRepetitions(previous_value,
                                        value, reps, tree_size,
                                        tree, extra_bits_data);
      previous_value = value;
    }
    i += reps;
  }
}