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
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int uint32_t ;
struct TYPE_3__ {float* literal_costs_; float* cost_dist_; float* cost_cmd_; size_t num_bytes_; size_t distance_histogram_size; float min_cost_cmd_; } ;
typedef  TYPE_1__ ZopfliCostModel ;

/* Variables and functions */
 size_t BROTLI_NUM_COMMAND_SYMBOLS ; 
 int /*<<< orphan*/  BrotliEstimateBitCostsForLiterals (size_t,size_t,size_t,int /*<<< orphan*/  const*,float*) ; 
 scalar_t__ FastLog2 (int) ; 

__attribute__((used)) static void ZopfliCostModelSetFromLiteralCosts(ZopfliCostModel* self,
                                               size_t position,
                                               const uint8_t* ringbuffer,
                                               size_t ringbuffer_mask) {
  float* literal_costs = self->literal_costs_;
  float literal_carry = 0.0;
  float* cost_dist = self->cost_dist_;
  float* cost_cmd = self->cost_cmd_;
  size_t num_bytes = self->num_bytes_;
  size_t i;
  BrotliEstimateBitCostsForLiterals(position, num_bytes, ringbuffer_mask,
                                    ringbuffer, &literal_costs[1]);
  literal_costs[0] = 0.0;
  for (i = 0; i < num_bytes; ++i) {
    literal_carry += literal_costs[i + 1];
    literal_costs[i + 1] = literal_costs[i] + literal_carry;
    literal_carry -= literal_costs[i + 1] - literal_costs[i];
  }
  for (i = 0; i < BROTLI_NUM_COMMAND_SYMBOLS; ++i) {
    cost_cmd[i] = (float)FastLog2(11 + (uint32_t)i);
  }
  for (i = 0; i < self->distance_histogram_size; ++i) {
    cost_dist[i] = (float)FastLog2(20 + (uint32_t)i);
  }
  self->min_cost_cmd_ = (float)FastLog2(11);
}