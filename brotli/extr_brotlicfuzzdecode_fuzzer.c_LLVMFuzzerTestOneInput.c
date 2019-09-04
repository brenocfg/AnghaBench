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
typedef  int /*<<< orphan*/  BrotliDecoderState ;
typedef  scalar_t__ BrotliDecoderResult ;

/* Variables and functions */
 scalar_t__ BROTLI_DECODER_RESULT_NEEDS_MORE_INPUT ; 
 scalar_t__ BROTLI_DECODER_RESULT_NEEDS_MORE_OUTPUT ; 
 int /*<<< orphan*/ * BrotliDecoderCreateInstance (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ BrotliDecoderDecompressStream (int /*<<< orphan*/ *,size_t*,int const**,size_t*,int**,size_t*) ; 
 int /*<<< orphan*/  BrotliDecoderDestroyInstance (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free (int*) ; 
 scalar_t__ malloc (int const) ; 

int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  size_t addend = 0;
  if (size > 0)
    addend = data[size - 1] & 7;
  const uint8_t* next_in = data;

  const int kBufferSize = 1024;
  uint8_t* buffer = (uint8_t*) malloc(kBufferSize);
  if (!buffer) {
    // OOM is out-of-scope here.
    return 0;
  }
  /* The biggest "magic number" in brotli is 16MiB - 16, so no need to check
     the cases with much longer output. */
  const size_t total_out_limit = (addend == 0) ? (1 << 26) : (1 << 24);
  size_t total_out = 0;

  BrotliDecoderState* state = BrotliDecoderCreateInstance(0, 0, 0);

  if (addend == 0)
    addend = size;
  /* Test both fast (addend == size) and slow (addend <= 7) decoding paths. */
  for (size_t i = 0; i < size;) {
    size_t next_i = i + addend;
    if (next_i > size)
      next_i = size;
    size_t avail_in = next_i - i;
    i = next_i;
    BrotliDecoderResult result = BROTLI_DECODER_RESULT_NEEDS_MORE_OUTPUT;
    while (result == BROTLI_DECODER_RESULT_NEEDS_MORE_OUTPUT) {
      size_t avail_out = kBufferSize;
      uint8_t* next_out = buffer;
      result = BrotliDecoderDecompressStream(
          state, &avail_in, &next_in, &avail_out, &next_out, &total_out);
      if (total_out > total_out_limit)
        break;
    }
    if (total_out > total_out_limit)
      break;
    if (result != BROTLI_DECODER_RESULT_NEEDS_MORE_INPUT)
      break;
  }

  BrotliDecoderDestroyInstance(state);
  free(buffer);
  return 0;
}