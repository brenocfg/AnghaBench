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
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int /*<<< orphan*/  BrotliDecoderState ;
typedef  scalar_t__ BrotliDecoderResult ;

/* Variables and functions */
 scalar_t__ BROTLI_DECODER_RESULT_ERROR ; 
 scalar_t__ BROTLI_DECODER_RESULT_SUCCESS ; 
 scalar_t__ BrotliDecoderDecompressStream (int /*<<< orphan*/ *,size_t*,int /*<<< orphan*/  const**,size_t*,int /*<<< orphan*/ **,size_t*) ; 
 int /*<<< orphan*/  BrotliDecoderStateCleanup (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  BrotliDecoderStateInit (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

BrotliDecoderResult BrotliDecoderDecompress(
    size_t encoded_size, const uint8_t* encoded_buffer, size_t* decoded_size,
    uint8_t* decoded_buffer) {
  BrotliDecoderState s;
  BrotliDecoderResult result;
  size_t total_out = 0;
  size_t available_in = encoded_size;
  const uint8_t* next_in = encoded_buffer;
  size_t available_out = *decoded_size;
  uint8_t* next_out = decoded_buffer;
  if (!BrotliDecoderStateInit(&s, 0, 0, 0)) {
    return BROTLI_DECODER_RESULT_ERROR;
  }
  result = BrotliDecoderDecompressStream(
      &s, &available_in, &next_in, &available_out, &next_out, &total_out);
  *decoded_size = total_out;
  BrotliDecoderStateCleanup(&s);
  if (result != BROTLI_DECODER_RESULT_SUCCESS) {
    result = BROTLI_DECODER_RESULT_ERROR;
  }
  return result;
}