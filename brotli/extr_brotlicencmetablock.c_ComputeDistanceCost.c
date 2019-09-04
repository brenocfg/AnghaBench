#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ uint32_t ;
typedef  int uint16_t ;
struct TYPE_10__ {scalar_t__ distance_postfix_bits; scalar_t__ num_direct_distance_codes; scalar_t__ max_distance; } ;
struct TYPE_9__ {int cmd_prefix_; int dist_prefix_; } ;
typedef  int /*<<< orphan*/  HistogramDistance ;
typedef  TYPE_1__ Command ;
typedef  TYPE_2__ BrotliDistanceParams ;
typedef  scalar_t__ BROTLI_BOOL ;

/* Variables and functions */
 scalar_t__ BROTLI_FALSE ; 
 scalar_t__ BROTLI_TRUE ; 
 double BrotliPopulationCostDistance (int /*<<< orphan*/ *) ; 
 scalar_t__ CommandCopyLen (TYPE_1__ const*) ; 
 scalar_t__ CommandRestoreDistanceCode (TYPE_1__ const*,TYPE_2__ const*) ; 
 int /*<<< orphan*/  HistogramAddDistance (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  HistogramClearDistance (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  PrefixEncodeCopyDistance (scalar_t__,scalar_t__,scalar_t__,int*,scalar_t__*) ; 

__attribute__((used)) static BROTLI_BOOL ComputeDistanceCost(const Command* cmds,
                                       size_t num_commands,
                                       const BrotliDistanceParams* orig_params,
                                       const BrotliDistanceParams* new_params,
                                       double* cost) {
  size_t i;
  BROTLI_BOOL equal_params = BROTLI_FALSE;
  uint16_t dist_prefix;
  uint32_t dist_extra;
  double extra_bits = 0.0;
  HistogramDistance histo;
  HistogramClearDistance(&histo);

  if (orig_params->distance_postfix_bits == new_params->distance_postfix_bits &&
      orig_params->num_direct_distance_codes ==
      new_params->num_direct_distance_codes) {
    equal_params = BROTLI_TRUE;
  }

  for (i = 0; i < num_commands; i++) {
    const Command* cmd = &cmds[i];
    if (CommandCopyLen(cmd) && cmd->cmd_prefix_ >= 128) {
      if (equal_params) {
        dist_prefix = cmd->dist_prefix_;
      } else {
        uint32_t distance = CommandRestoreDistanceCode(cmd, orig_params);
        if (distance > new_params->max_distance) {
          return BROTLI_FALSE;
        }
        PrefixEncodeCopyDistance(distance,
                                 new_params->num_direct_distance_codes,
                                 new_params->distance_postfix_bits,
                                 &dist_prefix,
                                 &dist_extra);
      }
      HistogramAddDistance(&histo, dist_prefix & 0x3FF);
      extra_bits += dist_prefix >> 10;
    }
  }

  *cost = BrotliPopulationCostDistance(&histo) + extra_bits;
  return BROTLI_TRUE;
}