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
typedef  size_t uint32_t ;
typedef  int /*<<< orphan*/  BROTLI_BOOL ;

/* Variables and functions */
 scalar_t__ FastLog2 (size_t const) ; 

__attribute__((used)) static void SetCost(const uint32_t* histogram, size_t histogram_size,
                    BROTLI_BOOL literal_histogram, float* cost) {
  size_t sum = 0;
  size_t missing_symbol_sum;
  float log2sum;
  float missing_symbol_cost;
  size_t i;
  for (i = 0; i < histogram_size; i++) {
    sum += histogram[i];
  }
  log2sum = (float)FastLog2(sum);
  missing_symbol_sum = sum;
  if (!literal_histogram) {
    for (i = 0; i < histogram_size; i++) {
      if (histogram[i] == 0) missing_symbol_sum++;
    }
  }
  missing_symbol_cost = (float)FastLog2(missing_symbol_sum) + 2;
  for (i = 0; i < histogram_size; i++) {
    if (histogram[i] == 0) {
      cost[i] = missing_symbol_cost;
      continue;
    }

    /* Shannon bits for this symbol. */
    cost[i] = log2sum - (float)FastLog2(histogram[i]);

    /* Cannot be coded with less than 1 bit */
    if (cost[i] < 1) cost[i] = 1;
  }
}