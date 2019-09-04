#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int uint32_t ;
struct TYPE_4__ {int data_size; int /*<<< orphan*/  const* data; int /*<<< orphan*/  data_ref; } ;
typedef  TYPE_1__ CodedBitstreamFragment ;
typedef  int /*<<< orphan*/  CodedBitstreamContext ;

/* Variables and functions */
 int /*<<< orphan*/ * avpriv_find_start_code (int /*<<< orphan*/  const*,int /*<<< orphan*/  const*,int*) ; 
 int ff_cbs_insert_unit_data (int /*<<< orphan*/ *,TYPE_1__*,int,int,int /*<<< orphan*/ *,size_t,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int cbs_mpeg2_split_fragment(CodedBitstreamContext *ctx,
                                    CodedBitstreamFragment *frag,
                                    int header)
{
    const uint8_t *start, *end;
    uint8_t *unit_data;
    uint32_t start_code = -1, next_start_code = -1;
    size_t unit_size;
    int err, i, unit_type;

    start = avpriv_find_start_code(frag->data, frag->data + frag->data_size,
                                   &start_code);
    for (i = 0;; i++) {
        end = avpriv_find_start_code(start, frag->data + frag->data_size,
                                     &next_start_code);

        unit_type = start_code & 0xff;

        // The start and end pointers point at to the byte following the
        // start_code_identifier in the start code that they found.
        if (end == frag->data + frag->data_size) {
            // We didn't find a start code, so this is the final unit.
            unit_size = end - (start - 1);
        } else {
            // Unit runs from start to the beginning of the start code
            // pointed to by end (including any padding zeroes).
            unit_size = (end - 4) - (start - 1);
        }

        unit_data = (uint8_t *)start - 1;

        err = ff_cbs_insert_unit_data(ctx, frag, i, unit_type,
                                      unit_data, unit_size, frag->data_ref);
        if (err < 0)
            return err;

        if (end == frag->data + frag->data_size)
            break;

        start_code = next_start_code;
        start = end;
    }

    return 0;
}