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
struct TYPE_3__ {scalar_t__ available_out_; } ;
typedef  TYPE_1__ BrotliEncoderState ;
typedef  int /*<<< orphan*/  BROTLI_BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  TO_BROTLI_BOOL (int) ; 

BROTLI_BOOL BrotliEncoderHasMoreOutput(BrotliEncoderState* s) {
  return TO_BROTLI_BOOL(s->available_out_ != 0);
}