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
typedef  int /*<<< orphan*/  uint32_t ;
struct TYPE_3__ {scalar_t__ state; int canny_ringbuffer_allocation; int /*<<< orphan*/  large_window; } ;
typedef  TYPE_1__ BrotliDecoderState ;
typedef  int BrotliDecoderParameter ;
typedef  int /*<<< orphan*/  BROTLI_BOOL ;

/* Variables and functions */
#define  BROTLI_DECODER_PARAM_DISABLE_RING_BUFFER_REALLOCATION 129 
#define  BROTLI_DECODER_PARAM_LARGE_WINDOW 128 
 int /*<<< orphan*/  BROTLI_FALSE ; 
 scalar_t__ BROTLI_STATE_UNINITED ; 
 int /*<<< orphan*/  BROTLI_TRUE ; 
 int /*<<< orphan*/  TO_BROTLI_BOOL (int) ; 

BROTLI_BOOL BrotliDecoderSetParameter(
    BrotliDecoderState* state, BrotliDecoderParameter p, uint32_t value) {
  if (state->state != BROTLI_STATE_UNINITED) return BROTLI_FALSE;
  switch (p) {
    case BROTLI_DECODER_PARAM_DISABLE_RING_BUFFER_REALLOCATION:
      state->canny_ringbuffer_allocation = !!value ? 0 : 1;
      return BROTLI_TRUE;

    case BROTLI_DECODER_PARAM_LARGE_WINDOW:
      state->large_window = TO_BROTLI_BOOL(!!value);
      return BROTLI_TRUE;

    default: return BROTLI_FALSE;
  }
}