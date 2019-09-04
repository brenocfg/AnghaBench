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
struct TYPE_4__ {int /*<<< orphan*/  partitioned_frame; int /*<<< orphan*/  progressive_frame; int /*<<< orphan*/  frame_pred_frame_dct; int /*<<< orphan*/  gop_picture_number; int /*<<< orphan*/  picture_in_gop_number; int /*<<< orphan*/  lambda2; int /*<<< orphan*/  lambda; int /*<<< orphan*/  qscale; int /*<<< orphan*/  b_code; int /*<<< orphan*/  f_code; int /*<<< orphan*/  current_picture; int /*<<< orphan*/  pict_type; } ;
typedef  TYPE_1__ MpegEncContext ;

/* Variables and functions */

__attribute__((used)) static void update_duplicate_context_after_me(MpegEncContext *dst,
                                              MpegEncContext *src)
{
#define COPY(a) dst->a= src->a
    COPY(pict_type);
    COPY(current_picture);
    COPY(f_code);
    COPY(b_code);
    COPY(qscale);
    COPY(lambda);
    COPY(lambda2);
    COPY(picture_in_gop_number);
    COPY(gop_picture_number);
    COPY(frame_pred_frame_dct); // FIXME don't set in encode_header
    COPY(progressive_frame);    // FIXME don't set in encode_header
    COPY(partitioned_frame);    // FIXME don't set in encode_header
#undef COPY
}