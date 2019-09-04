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
struct TYPE_4__ {int slice_count; int /*<<< orphan*/ * slice_offset; int /*<<< orphan*/  thread_safe_callbacks; int /*<<< orphan*/  reordered_opaque; int /*<<< orphan*/  frame_number; int /*<<< orphan*/  skip_loop_filter; int /*<<< orphan*/  subtitle_header; int /*<<< orphan*/  flags2; int /*<<< orphan*/  slice_flags; int /*<<< orphan*/  debug_mv; int /*<<< orphan*/  debug; int /*<<< orphan*/  opaque; int /*<<< orphan*/  get_buffer2; int /*<<< orphan*/  draw_horiz_band; int /*<<< orphan*/  flags; } ;
typedef  TYPE_1__ AVCodecContext ;

/* Variables and functions */
 int av_reallocp_array (int /*<<< orphan*/ **,int,int) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static int update_context_from_user(AVCodecContext *dst, AVCodecContext *src)
{
#define copy_fields(s, e) memcpy(&dst->s, &src->s, (char*)&dst->e - (char*)&dst->s);
    dst->flags          = src->flags;

    dst->draw_horiz_band= src->draw_horiz_band;
    dst->get_buffer2    = src->get_buffer2;

    dst->opaque   = src->opaque;
    dst->debug    = src->debug;
    dst->debug_mv = src->debug_mv;

    dst->slice_flags = src->slice_flags;
    dst->flags2      = src->flags2;

    copy_fields(skip_loop_filter, subtitle_header);

    dst->frame_number     = src->frame_number;
    dst->reordered_opaque = src->reordered_opaque;
    dst->thread_safe_callbacks = src->thread_safe_callbacks;

    if (src->slice_count && src->slice_offset) {
        if (dst->slice_count < src->slice_count) {
            int err = av_reallocp_array(&dst->slice_offset, src->slice_count,
                                        sizeof(*dst->slice_offset));
            if (err < 0)
                return err;
        }
        memcpy(dst->slice_offset, src->slice_offset,
               src->slice_count * sizeof(*dst->slice_offset));
    }
    dst->slice_count = src->slice_count;
    return 0;
#undef copy_fields
}