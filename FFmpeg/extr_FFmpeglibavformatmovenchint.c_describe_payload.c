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
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int /*<<< orphan*/  HintSampleQueue ;
typedef  int /*<<< orphan*/  AVIOContext ;

/* Variables and functions */
 scalar_t__ find_sample_match (int /*<<< orphan*/  const*,int,int /*<<< orphan*/ *,int*,int*,int*,int*) ; 
 int /*<<< orphan*/  output_immediate (int /*<<< orphan*/  const*,int,int /*<<< orphan*/ *,int*) ; 
 int /*<<< orphan*/  output_match (int /*<<< orphan*/ *,int,int,int,int*) ; 

__attribute__((used)) static void describe_payload(const uint8_t *data, int size,
                             AVIOContext *out, int *entries,
                             HintSampleQueue *queue)
{
    /* Describe the payload using different constructors */
    while (size > 0) {
        int match_sample, match_offset, match_len, pos;
        if (find_sample_match(data, size, queue, &pos, &match_sample,
                              &match_offset, &match_len) < 0)
            break;
        output_immediate(data, pos, out, entries);
        data += pos;
        size -= pos;
        output_match(out, match_sample, match_offset, match_len, entries);
        data += match_len;
        size -= match_len;
    }
    output_immediate(data, size, out, entries);
}