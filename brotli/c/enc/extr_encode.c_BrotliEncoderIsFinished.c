#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {scalar_t__ stream_state_; } ;
typedef  TYPE_1__ BrotliEncoderState ;
typedef  int /*<<< orphan*/  BROTLI_BOOL ;

/* Variables and functions */
 scalar_t__ BROTLI_STREAM_FINISHED ; 
 int /*<<< orphan*/  BrotliEncoderHasMoreOutput (TYPE_1__*) ; 
 int /*<<< orphan*/  TO_BROTLI_BOOL (int) ; 

BROTLI_BOOL BrotliEncoderIsFinished(BrotliEncoderState* s) {
  return TO_BROTLI_BOOL(s->stream_state_ == BROTLI_STREAM_FINISHED &&
      !BrotliEncoderHasMoreOutput(s));
}