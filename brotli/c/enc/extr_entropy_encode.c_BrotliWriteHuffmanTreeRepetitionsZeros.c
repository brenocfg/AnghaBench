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
typedef  size_t uint8_t ;

/* Variables and functions */
 size_t BROTLI_REPEAT_ZERO_CODE_LENGTH ; 
 scalar_t__ BROTLI_TRUE ; 
 int /*<<< orphan*/  Reverse (size_t*,size_t,size_t) ; 

__attribute__((used)) static void BrotliWriteHuffmanTreeRepetitionsZeros(
    size_t repetitions,
    size_t* tree_size,
    uint8_t* tree,
    uint8_t* extra_bits_data) {
  if (repetitions == 11) {
    tree[*tree_size] = 0;
    extra_bits_data[*tree_size] = 0;
    ++(*tree_size);
    --repetitions;
  }
  if (repetitions < 3) {
    size_t i;
    for (i = 0; i < repetitions; ++i) {
      tree[*tree_size] = 0;
      extra_bits_data[*tree_size] = 0;
      ++(*tree_size);
    }
  } else {
    size_t start = *tree_size;
    repetitions -= 3;
    while (BROTLI_TRUE) {
      tree[*tree_size] = BROTLI_REPEAT_ZERO_CODE_LENGTH;
      extra_bits_data[*tree_size] = repetitions & 0x7;
      ++(*tree_size);
      repetitions >>= 3;
      if (repetitions == 0) {
        break;
      }
      --repetitions;
    }
    Reverse(tree, start, *tree_size);
    Reverse(extra_bits_data, start, *tree_size);
  }
}