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
typedef  int uint8_t ;
typedef  int uint32_t ;

/* Variables and functions */
 int /*<<< orphan*/  memset (int*,int /*<<< orphan*/ ,size_t) ; 

void BrotliOptimizeHuffmanCountsForRle(size_t length, uint32_t* counts,
                                       uint8_t* good_for_rle) {
  size_t nonzero_count = 0;
  size_t stride;
  size_t limit;
  size_t sum;
  const size_t streak_limit = 1240;
  /* Let's make the Huffman code more compatible with RLE encoding. */
  size_t i;
  for (i = 0; i < length; i++) {
    if (counts[i]) {
      ++nonzero_count;
    }
  }
  if (nonzero_count < 16) {
    return;
  }
  while (length != 0 && counts[length - 1] == 0) {
    --length;
  }
  if (length == 0) {
    return;  /* All zeros. */
  }
  /* Now counts[0..length - 1] does not have trailing zeros. */
  {
    size_t nonzeros = 0;
    uint32_t smallest_nonzero = 1 << 30;
    for (i = 0; i < length; ++i) {
      if (counts[i] != 0) {
        ++nonzeros;
        if (smallest_nonzero > counts[i]) {
          smallest_nonzero = counts[i];
        }
      }
    }
    if (nonzeros < 5) {
      /* Small histogram will model it well. */
      return;
    }
    if (smallest_nonzero < 4) {
      size_t zeros = length - nonzeros;
      if (zeros < 6) {
        for (i = 1; i < length - 1; ++i) {
          if (counts[i - 1] != 0 && counts[i] == 0 && counts[i + 1] != 0) {
            counts[i] = 1;
          }
        }
      }
    }
    if (nonzeros < 28) {
      return;
    }
  }
  /* 2) Let's mark all population counts that already can be encoded
     with an RLE code. */
  memset(good_for_rle, 0, length);
  {
    /* Let's not spoil any of the existing good RLE codes.
       Mark any seq of 0's that is longer as 5 as a good_for_rle.
       Mark any seq of non-0's that is longer as 7 as a good_for_rle. */
    uint32_t symbol = counts[0];
    size_t step = 0;
    for (i = 0; i <= length; ++i) {
      if (i == length || counts[i] != symbol) {
        if ((symbol == 0 && step >= 5) ||
            (symbol != 0 && step >= 7)) {
          size_t k;
          for (k = 0; k < step; ++k) {
            good_for_rle[i - k - 1] = 1;
          }
        }
        step = 1;
        if (i != length) {
          symbol = counts[i];
        }
      } else {
        ++step;
      }
    }
  }
  /* 3) Let's replace those population counts that lead to more RLE codes.
     Math here is in 24.8 fixed point representation. */
  stride = 0;
  limit = 256 * (counts[0] + counts[1] + counts[2]) / 3 + 420;
  sum = 0;
  for (i = 0; i <= length; ++i) {
    if (i == length || good_for_rle[i] ||
        (i != 0 && good_for_rle[i - 1]) ||
        (256 * counts[i] - limit + streak_limit) >= 2 * streak_limit) {
      if (stride >= 4 || (stride >= 3 && sum == 0)) {
        size_t k;
        /* The stride must end, collapse what we have, if we have enough (4). */
        size_t count = (sum + stride / 2) / stride;
        if (count == 0) {
          count = 1;
        }
        if (sum == 0) {
          /* Don't make an all zeros stride to be upgraded to ones. */
          count = 0;
        }
        for (k = 0; k < stride; ++k) {
          /* We don't want to change value at counts[i],
             that is already belonging to the next stride. Thus - 1. */
          counts[i - k - 1] = (uint32_t)count;
        }
      }
      stride = 0;
      sum = 0;
      if (i < length - 2) {
        /* All interesting strides have a count of at least 4, */
        /* at least when non-zeros. */
        limit = 256 * (counts[i] + counts[i + 1] + counts[i + 2]) / 3 + 420;
      } else if (i < length) {
        limit = 256 * counts[i];
      } else {
        limit = 0;
      }
    }
    ++stride;
    if (i != length) {
      sum += counts[i];
      if (stride >= 4) {
        limit = (256 * sum + stride / 2) / stride;
      }
      if (stride == 4) {
        limit += 120;
      }
    }
  }
}