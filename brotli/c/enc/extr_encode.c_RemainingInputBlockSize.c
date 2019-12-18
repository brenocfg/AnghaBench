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
typedef  size_t uint64_t ;
typedef  int /*<<< orphan*/  BrotliEncoderState ;

/* Variables and functions */
 size_t InputBlockSize (int /*<<< orphan*/ *) ; 
 size_t UnprocessedInputSize (int /*<<< orphan*/ *) ; 

__attribute__((used)) static size_t RemainingInputBlockSize(BrotliEncoderState* s) {
  const uint64_t delta = UnprocessedInputSize(s);
  size_t block_size = InputBlockSize(s);
  if (delta >= block_size) return 0;
  return block_size - (size_t)delta;
}