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
struct TYPE_4__ {scalar_t__ nb_refs; scalar_t__ nb_dpb_pics; int* ref_count; struct TYPE_4__* prev; struct TYPE_4__** dpb; struct TYPE_4__** refs; } ;
typedef  TYPE_1__ VAAPIEncodePicture ;
typedef  int /*<<< orphan*/  AVCodecContext ;

/* Variables and functions */
 scalar_t__ MAX_DPB_SIZE ; 
 scalar_t__ MAX_PICTURE_REFERENCES ; 
 int /*<<< orphan*/  av_assert0 (int) ; 

__attribute__((used)) static void vaapi_encode_add_ref(AVCodecContext *avctx,
                                 VAAPIEncodePicture *pic,
                                 VAAPIEncodePicture *target,
                                 int is_ref, int in_dpb, int prev)
{
    int refs = 0;

    if (is_ref) {
        av_assert0(pic != target);
        av_assert0(pic->nb_refs < MAX_PICTURE_REFERENCES);
        pic->refs[pic->nb_refs++] = target;
        ++refs;
    }

    if (in_dpb) {
        av_assert0(pic->nb_dpb_pics < MAX_DPB_SIZE);
        pic->dpb[pic->nb_dpb_pics++] = target;
        ++refs;
    }

    if (prev) {
        av_assert0(!pic->prev);
        pic->prev = target;
        ++refs;
    }

    target->ref_count[0] += refs;
    target->ref_count[1] += refs;
}