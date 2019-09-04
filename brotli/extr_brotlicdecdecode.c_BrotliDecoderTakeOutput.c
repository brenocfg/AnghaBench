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
typedef  int /*<<< orphan*/  const uint8_t ;
struct TYPE_6__ {scalar_t__ ringbuffer; scalar_t__ error_code; } ;
typedef  TYPE_1__ BrotliDecoderState ;
typedef  scalar_t__ BrotliDecoderErrorCode ;

/* Variables and functions */
 scalar_t__ BROTLI_DECODER_NEEDS_MORE_OUTPUT ; 
 scalar_t__ BROTLI_DECODER_SUCCESS ; 
 int /*<<< orphan*/  BROTLI_TRUE ; 
 int /*<<< orphan*/  SaveErrorCode (TYPE_1__*,scalar_t__) ; 
 int /*<<< orphan*/  WrapRingBuffer (TYPE_1__*) ; 
 scalar_t__ WriteRingBuffer (TYPE_1__*,size_t*,int /*<<< orphan*/  const**,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

const uint8_t* BrotliDecoderTakeOutput(BrotliDecoderState* s, size_t* size) {
  uint8_t* result = 0;
  size_t available_out = *size ? *size : 1u << 24;
  size_t requested_out = available_out;
  BrotliDecoderErrorCode status;
  if ((s->ringbuffer == 0) || ((int)s->error_code < 0)) {
    *size = 0;
    return 0;
  }
  WrapRingBuffer(s);
  status = WriteRingBuffer(s, &available_out, &result, 0, BROTLI_TRUE);
  /* Either WriteRingBuffer returns those "success" codes... */
  if (status == BROTLI_DECODER_SUCCESS ||
      status == BROTLI_DECODER_NEEDS_MORE_OUTPUT) {
    *size = requested_out - available_out;
  } else {
    /* ... or stream is broken. Normally this should be caught by
       BrotliDecoderDecompressStream, this is just a safeguard. */
    if ((int)status < 0) SaveErrorCode(s, status);
    *size = 0;
    result = 0;
  }
  return result;
}