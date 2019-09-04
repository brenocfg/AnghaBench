#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
struct TYPE_6__ {int offset; int size; int sample_number; int /*<<< orphan*/  data; } ;
struct TYPE_5__ {scalar_t__ len; TYPE_2__* samples; } ;
typedef  TYPE_1__ HintSampleQueue ;
typedef  TYPE_2__ HintSample ;

/* Variables and functions */
 scalar_t__ match_segments (int /*<<< orphan*/  const*,int,int /*<<< orphan*/ ,int,int,int*,int*,int*) ; 
 int /*<<< orphan*/  sample_queue_pop (TYPE_1__*) ; 

__attribute__((used)) static int find_sample_match(const uint8_t *data, int len,
                             HintSampleQueue *queue, int *pos,
                             int *match_sample, int *match_offset,
                             int *match_len)
{
    while (queue->len > 0) {
        HintSample *sample = &queue->samples[0];
        /* If looking for matches in a new sample, skip the first 5 bytes,
         * since they often may be modified/removed in the output packet. */
        if (sample->offset == 0 && sample->size > 5)
            sample->offset = 5;

        if (match_segments(data, len, sample->data, sample->offset,
                           sample->size, pos, match_offset, match_len) == 0) {
            *match_sample = sample->sample_number;
            /* Next time, look for matches at this offset, with a little
             * margin to this match. */
            sample->offset = *match_offset + *match_len + 5;
            if (sample->offset + 10 >= sample->size)
                sample_queue_pop(queue); /* Not enough useful data left */
            return 0;
        }

        if (sample->offset < 10 && sample->size > 20) {
            /* No match found from the start of the sample,
             * try from the middle of the sample instead. */
            sample->offset = sample->size/2;
        } else {
            /* No match for this sample, remove it */
            sample_queue_pop(queue);
        }
    }
    return -1;
}