#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {float cost; } ;
struct TYPE_5__ {TYPE_1__ u; } ;
typedef  TYPE_2__ ZopfliNode ;

/* Variables and functions */

__attribute__((used)) static size_t ComputeMinimumCopyLength(const float start_cost,
                                       const ZopfliNode* nodes,
                                       const size_t num_bytes,
                                       const size_t pos) {
  /* Compute the minimum possible cost of reaching any future position. */
  float min_cost = start_cost;
  size_t len = 2;
  size_t next_len_bucket = 4;
  size_t next_len_offset = 10;
  while (pos + len <= num_bytes && nodes[pos + len].u.cost <= min_cost) {
    /* We already reached (pos + len) with no more cost than the minimum
       possible cost of reaching anything from this pos, so there is no point in
       looking for lengths <= len. */
    ++len;
    if (len == next_len_offset) {
      /* We reached the next copy length code bucket, so we add one more
         extra bit to the minimum cost. */
      min_cost += 1.0f;
      next_len_offset += next_len_bucket;
      next_len_bucket *= 2;
    }
  }
  return len;
}