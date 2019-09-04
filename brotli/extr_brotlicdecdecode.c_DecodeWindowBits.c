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
typedef  int uint32_t ;
struct TYPE_3__ {int window_bits; scalar_t__ large_window; } ;
typedef  TYPE_1__ BrotliDecoderState ;
typedef  int /*<<< orphan*/  BrotliDecoderErrorCode ;
typedef  int /*<<< orphan*/  BrotliBitReader ;
typedef  scalar_t__ BROTLI_BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  BROTLI_DECODER_ERROR_FORMAT_WINDOW_BITS ; 
 int /*<<< orphan*/  BROTLI_DECODER_SUCCESS ; 
 int /*<<< orphan*/  BROTLI_FAILURE (int /*<<< orphan*/ ) ; 
 scalar_t__ BROTLI_FALSE ; 
 scalar_t__ BROTLI_TRUE ; 
 int /*<<< orphan*/  BrotliTakeBits (int /*<<< orphan*/ *,int,int*) ; 

__attribute__((used)) static BrotliDecoderErrorCode DecodeWindowBits(BrotliDecoderState* s,
                                               BrotliBitReader* br) {
  uint32_t n;
  BROTLI_BOOL large_window = s->large_window;
  s->large_window = BROTLI_FALSE;
  BrotliTakeBits(br, 1, &n);
  if (n == 0) {
    s->window_bits = 16;
    return BROTLI_DECODER_SUCCESS;
  }
  BrotliTakeBits(br, 3, &n);
  if (n != 0) {
    s->window_bits = 17 + n;
    return BROTLI_DECODER_SUCCESS;
  }
  BrotliTakeBits(br, 3, &n);
  if (n == 1) {
    if (large_window) {
      BrotliTakeBits(br, 1, &n);
      if (n == 1) {
        return BROTLI_FAILURE(BROTLI_DECODER_ERROR_FORMAT_WINDOW_BITS);
      }
      s->large_window = BROTLI_TRUE;
      return BROTLI_DECODER_SUCCESS;
    } else {
      return BROTLI_FAILURE(BROTLI_DECODER_ERROR_FORMAT_WINDOW_BITS);
    }
  }
  if (n != 0) {
    s->window_bits = 8 + n;
    return BROTLI_DECODER_SUCCESS;
  }
  s->window_bits = 17;
  return BROTLI_DECODER_SUCCESS;
}