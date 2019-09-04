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
typedef  scalar_t__ uint64_t ;
struct TYPE_3__ {scalar_t__ last_processed_pos_; scalar_t__ input_pos_; } ;
typedef  TYPE_1__ BrotliEncoderState ;

/* Variables and functions */

__attribute__((used)) static uint64_t UnprocessedInputSize(BrotliEncoderState* s) {
  return s->input_pos_ - s->last_processed_pos_;
}