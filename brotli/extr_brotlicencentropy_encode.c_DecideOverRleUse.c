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
typedef  scalar_t__ uint8_t ;
typedef  int /*<<< orphan*/  BROTLI_BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  TO_BROTLI_BOOL (int) ; 

__attribute__((used)) static void DecideOverRleUse(const uint8_t* depth, const size_t length,
                             BROTLI_BOOL* use_rle_for_non_zero,
                             BROTLI_BOOL* use_rle_for_zero) {
  size_t total_reps_zero = 0;
  size_t total_reps_non_zero = 0;
  size_t count_reps_zero = 1;
  size_t count_reps_non_zero = 1;
  size_t i;
  for (i = 0; i < length;) {
    const uint8_t value = depth[i];
    size_t reps = 1;
    size_t k;
    for (k = i + 1; k < length && depth[k] == value; ++k) {
      ++reps;
    }
    if (reps >= 3 && value == 0) {
      total_reps_zero += reps;
      ++count_reps_zero;
    }
    if (reps >= 4 && value != 0) {
      total_reps_non_zero += reps;
      ++count_reps_non_zero;
    }
    i += reps;
  }
  *use_rle_for_non_zero =
      TO_BROTLI_BOOL(total_reps_non_zero > count_reps_non_zero * 2);
  *use_rle_for_zero = TO_BROTLI_BOOL(total_reps_zero > count_reps_zero * 2);
}