#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ uint8_t ;
typedef  scalar_t__ uint64_t ;
typedef  int uint32_t ;
struct TYPE_8__ {scalar_t__ lgwin; int /*<<< orphan*/  dist; } ;
struct TYPE_7__ {scalar_t__* buffer_; int mask_; } ;
struct TYPE_10__ {int num_commands_; scalar_t__ last_processed_pos_; TYPE_2__ params; scalar_t__* dist_cache_; TYPE_1__ ringbuffer_; TYPE_3__* commands_; } ;
struct TYPE_9__ {int copy_len_; int dist_prefix_; int /*<<< orphan*/  cmd_prefix_; int /*<<< orphan*/  insert_len_; } ;
typedef  TYPE_3__ Command ;
typedef  TYPE_4__ BrotliEncoderState ;

/* Variables and functions */
 int BROTLI_NUM_DISTANCE_SHORT_CODES ; 
 scalar_t__ BROTLI_WINDOW_GAP ; 
 int CommandRestoreDistanceCode (TYPE_3__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  GetLengthCode (int /*<<< orphan*/ ,size_t,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  TO_BROTLI_BOOL (int) ; 

__attribute__((used)) static void ExtendLastCommand(BrotliEncoderState* s, uint32_t* bytes,
                              uint32_t* wrapped_last_processed_pos) {
  Command* last_command = &s->commands_[s->num_commands_ - 1];
  const uint8_t* data = s->ringbuffer_.buffer_;
  const uint32_t mask = s->ringbuffer_.mask_;
  uint64_t max_backward_distance =
      (((uint64_t)1) << s->params.lgwin) - BROTLI_WINDOW_GAP;
  uint64_t last_copy_len = last_command->copy_len_ & 0x1FFFFFF;
  uint64_t last_processed_pos = s->last_processed_pos_ - last_copy_len;
  uint64_t max_distance = last_processed_pos < max_backward_distance ?
      last_processed_pos : max_backward_distance;
  uint64_t cmd_dist = (uint64_t)s->dist_cache_[0];
  uint32_t distance_code = CommandRestoreDistanceCode(last_command,
                                                      &s->params.dist);
  if (distance_code < BROTLI_NUM_DISTANCE_SHORT_CODES ||
      distance_code - (BROTLI_NUM_DISTANCE_SHORT_CODES - 1) == cmd_dist) {
    if (cmd_dist <= max_distance) {
      while (*bytes != 0 && data[*wrapped_last_processed_pos & mask] ==
             data[(*wrapped_last_processed_pos - cmd_dist) & mask]) {
        last_command->copy_len_++;
        (*bytes)--;
        (*wrapped_last_processed_pos)++;
      }
    } else {
    }
    /* The copy length is at most the metablock size, and thus expressible. */
    GetLengthCode(last_command->insert_len_,
                  (size_t)((int)(last_command->copy_len_ & 0x1FFFFFF) +
                           (int)(last_command->copy_len_ >> 25)),
                  TO_BROTLI_BOOL((last_command->dist_prefix_ & 0x3FF) == 0),
                  &last_command->cmd_prefix_);
  }
}