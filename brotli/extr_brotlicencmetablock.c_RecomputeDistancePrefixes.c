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
struct TYPE_10__ {scalar_t__ distance_postfix_bits; scalar_t__ num_direct_distance_codes; } ;
struct TYPE_9__ {int cmd_prefix_; int /*<<< orphan*/  dist_extra_; int /*<<< orphan*/  dist_prefix_; } ;
typedef  TYPE_1__ Command ;
typedef  TYPE_2__ BrotliDistanceParams ;

/* Variables and functions */
 scalar_t__ CommandCopyLen (TYPE_1__*) ; 
 int /*<<< orphan*/  CommandRestoreDistanceCode (TYPE_1__*,TYPE_2__ const*) ; 
 int /*<<< orphan*/  PrefixEncodeCopyDistance (int /*<<< orphan*/ ,scalar_t__,scalar_t__,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void RecomputeDistancePrefixes(Command* cmds,
                                      size_t num_commands,
                                      const BrotliDistanceParams* orig_params,
                                      const BrotliDistanceParams* new_params) {
  size_t i;

  if (orig_params->distance_postfix_bits == new_params->distance_postfix_bits &&
      orig_params->num_direct_distance_codes ==
      new_params->num_direct_distance_codes) {
    return;
  }

  for (i = 0; i < num_commands; ++i) {
    Command* cmd = &cmds[i];
    if (CommandCopyLen(cmd) && cmd->cmd_prefix_ >= 128) {
      PrefixEncodeCopyDistance(CommandRestoreDistanceCode(cmd, orig_params),
                               new_params->num_direct_distance_codes,
                               new_params->distance_postfix_bits,
                               &cmd->dist_prefix_,
                               &cmd->dist_extra_);
    }
  }
}