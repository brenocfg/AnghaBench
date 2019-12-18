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
struct TYPE_4__ {int data_size; int /*<<< orphan*/  data_ref; int /*<<< orphan*/  const* data; } ;
typedef  int CodedBitstreamUnitType ;
typedef  TYPE_1__ CodedBitstreamFragment ;
typedef  int /*<<< orphan*/  CodedBitstreamContext ;

/* Variables and functions */
 int AVERROR_INVALIDDATA ; 
 int /*<<< orphan*/ * avpriv_find_start_code (int /*<<< orphan*/  const*,int /*<<< orphan*/  const*,int*) ; 
 int ff_cbs_insert_unit_data (int /*<<< orphan*/ *,TYPE_1__*,int,int,int /*<<< orphan*/ *,size_t,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int cbs_mpeg2_split_fragment(CodedBitstreamContext *ctx,
                                    CodedBitstreamFragment *frag,
                                    int header)
{
    const uint8_t *start, *end;
    CodedBitstreamUnitType unit_type;
    uint32_t start_code = -1;
    size_t unit_size;
    int err, i, final = 0;

    start = avpriv_find_start_code(frag->data, frag->data + frag->data_size,
                                   &start_code);
    if (start_code >> 8 != 0x000001) {
        // No start code found.
        return AVERROR_INVALIDDATA;
    }

    for (i = 0;; i++) {
        unit_type = start_code & 0xff;

        if (start == frag->data + frag->data_size) {
            // The last four bytes form a start code which constitutes
            // a unit of its own.  In this situation avpriv_find_start_code
            // won't modify start_code at all so modify start_code so that
            // the next unit will be treated as the last unit.
            start_code = 0;
        }

        end = avpriv_find_start_code(start--, frag->data + frag->data_size,
                                     &start_code);

        // start points to the byte containing the start_code_identifier
        // (may be the last byte of fragment->data); end points to the byte
        // following the byte containing the start code identifier (or to
        // the end of fragment->data).
        if (start_code >> 8 == 0x000001) {
            // Unit runs from start to the beginning of the start code
            // pointed to by end (including any padding zeroes).
            unit_size = (end - 4) - start;
        } else {
           // We didn't find a start code, so this is the final unit.
           unit_size = end - start;
           final     = 1;
        }

        err = ff_cbs_insert_unit_data(ctx, frag, i, unit_type, (uint8_t*)start,
                                      unit_size, frag->data_ref);
        if (err < 0)
            return err;

        if (final)
            break;

        start = end;
    }

    return 0;
}