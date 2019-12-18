#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_3__ ;
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
struct TYPE_12__ {int b_depth; int is_reference; struct TYPE_12__** refs; void* type; struct TYPE_12__* next; } ;
typedef  TYPE_1__ VAAPIEncodePicture ;
struct TYPE_13__ {int max_b_depth; } ;
typedef  TYPE_2__ VAAPIEncodeContext ;
struct TYPE_14__ {TYPE_2__* priv_data; } ;
typedef  TYPE_3__ AVCodecContext ;

/* Variables and functions */
 void* PICTURE_TYPE_B ; 
 int /*<<< orphan*/  av_assert0 (int) ; 
 int /*<<< orphan*/  vaapi_encode_add_ref (TYPE_3__*,TYPE_1__*,TYPE_1__*,int,int,int) ; 

__attribute__((used)) static void vaapi_encode_set_b_pictures(AVCodecContext *avctx,
                                        VAAPIEncodePicture *start,
                                        VAAPIEncodePicture *end,
                                        VAAPIEncodePicture *prev,
                                        int current_depth,
                                        VAAPIEncodePicture **last)
{
    VAAPIEncodeContext *ctx = avctx->priv_data;
    VAAPIEncodePicture *pic, *next, *ref;
    int i, len;

    av_assert0(start && end && start != end && start->next != end);

    // If we are at the maximum depth then encode all pictures as
    // non-referenced B-pictures.  Also do this if there is exactly one
    // picture left, since there will be nothing to reference it.
    if (current_depth == ctx->max_b_depth || start->next->next == end) {
        for (pic = start->next; pic; pic = pic->next) {
            if (pic == end)
                break;
            pic->type    = PICTURE_TYPE_B;
            pic->b_depth = current_depth;

            vaapi_encode_add_ref(avctx, pic, start, 1, 1, 0);
            vaapi_encode_add_ref(avctx, pic, end,   1, 1, 0);
            vaapi_encode_add_ref(avctx, pic, prev,  0, 0, 1);

            for (ref = end->refs[1]; ref; ref = ref->refs[1])
                vaapi_encode_add_ref(avctx, pic, ref, 0, 1, 0);
        }
        *last = prev;

    } else {
        // Split the current list at the midpoint with a referenced
        // B-picture, then descend into each side separately.
        len = 0;
        for (pic = start->next; pic != end; pic = pic->next)
            ++len;
        for (pic = start->next, i = 1; 2 * i < len; pic = pic->next, i++);

        pic->type    = PICTURE_TYPE_B;
        pic->b_depth = current_depth;

        pic->is_reference = 1;

        vaapi_encode_add_ref(avctx, pic, pic,   0, 1, 0);
        vaapi_encode_add_ref(avctx, pic, start, 1, 1, 0);
        vaapi_encode_add_ref(avctx, pic, end,   1, 1, 0);
        vaapi_encode_add_ref(avctx, pic, prev,  0, 0, 1);

        for (ref = end->refs[1]; ref; ref = ref->refs[1])
            vaapi_encode_add_ref(avctx, pic, ref, 0, 1, 0);

        if (i > 1)
            vaapi_encode_set_b_pictures(avctx, start, pic, pic,
                                        current_depth + 1, &next);
        else
            next = pic;

        vaapi_encode_set_b_pictures(avctx, pic, end, next,
                                    current_depth + 1, last);
    }
}