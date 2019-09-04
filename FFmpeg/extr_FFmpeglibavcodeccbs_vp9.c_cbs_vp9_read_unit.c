#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int data_size; scalar_t__ data; int /*<<< orphan*/  data_ref; } ;
typedef  TYPE_1__ VP9RawFrame ;
struct TYPE_7__ {int data_size; int /*<<< orphan*/  data; int /*<<< orphan*/  data_ref; TYPE_1__* content; } ;
typedef  int /*<<< orphan*/  GetBitContext ;
typedef  TYPE_2__ CodedBitstreamUnit ;
typedef  int /*<<< orphan*/  CodedBitstreamContext ;

/* Variables and functions */
 int AVERROR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ENOMEM ; 
 int /*<<< orphan*/  av_assert0 (int) ; 
 int /*<<< orphan*/  av_buffer_ref (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cbs_vp9_free_frame ; 
 int cbs_vp9_read_frame (int /*<<< orphan*/ *,int /*<<< orphan*/ *,TYPE_1__*) ; 
 int ff_cbs_alloc_unit_content (int /*<<< orphan*/ *,TYPE_2__*,int,int /*<<< orphan*/ *) ; 
 int get_bits_count (int /*<<< orphan*/ *) ; 
 int init_get_bits (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int cbs_vp9_read_unit(CodedBitstreamContext *ctx,
                             CodedBitstreamUnit *unit)
{
    VP9RawFrame *frame;
    GetBitContext gbc;
    int err, pos;

    err = init_get_bits(&gbc, unit->data, 8 * unit->data_size);
    if (err < 0)
        return err;

    err = ff_cbs_alloc_unit_content(ctx, unit, sizeof(*frame),
                                    &cbs_vp9_free_frame);
    if (err < 0)
        return err;
    frame = unit->content;

    err = cbs_vp9_read_frame(ctx, &gbc, frame);
    if (err < 0)
        return err;

    pos = get_bits_count(&gbc);
    av_assert0(pos % 8 == 0);
    pos /= 8;
    av_assert0(pos <= unit->data_size);

    if (pos == unit->data_size) {
        // No data (e.g. a show-existing-frame frame).
    } else {
        frame->data_ref = av_buffer_ref(unit->data_ref);
        if (!frame->data_ref)
            return AVERROR(ENOMEM);

        frame->data      = unit->data      + pos;
        frame->data_size = unit->data_size - pos;
    }

    return 0;
}