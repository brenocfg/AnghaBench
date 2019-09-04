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

/* Variables and functions */

size_t BrotliEncoderMaxCompressedSize(size_t input_size) {
  /* [window bits / empty metadata] + N * [uncompressed] + [last empty] */
  size_t num_large_blocks = input_size >> 14;
  size_t overhead = 2 + (4 * num_large_blocks) + 3 + 1;
  size_t result = input_size + overhead;
  if (input_size == 0) return 2;
  return (result < input_size) ? 0 : result;
}