#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  pb; TYPE_1__* avctx; scalar_t__ quarter_sample; scalar_t__ max_b_frames; } ;
struct TYPE_4__ {int profile; int level; } ;
typedef  TYPE_2__ MpegEncContext ;

/* Variables and functions */
 int FF_LEVEL_UNKNOWN ; 
 int FF_PROFILE_UNKNOWN ; 
 int VISUAL_OBJ_STARTCODE ; 
 int VOS_STARTCODE ; 
 int /*<<< orphan*/  ff_mpeg4_stuffing (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  put_bits (int /*<<< orphan*/ *,int,int) ; 

__attribute__((used)) static void mpeg4_encode_visual_object_header(MpegEncContext *s)
{
    int profile_and_level_indication;
    int vo_ver_id;

    if (s->avctx->profile != FF_PROFILE_UNKNOWN) {
        profile_and_level_indication = s->avctx->profile << 4;
    } else if (s->max_b_frames || s->quarter_sample) {
        profile_and_level_indication = 0xF0;  // adv simple
    } else {
        profile_and_level_indication = 0x00;  // simple
    }

    if (s->avctx->level != FF_LEVEL_UNKNOWN)
        profile_and_level_indication |= s->avctx->level;
    else
        profile_and_level_indication |= 1;   // level 1

    if (profile_and_level_indication >> 4 == 0xF)
        vo_ver_id = 5;
    else
        vo_ver_id = 1;

    // FIXME levels

    put_bits(&s->pb, 16, 0);
    put_bits(&s->pb, 16, VOS_STARTCODE);

    put_bits(&s->pb, 8, profile_and_level_indication);

    put_bits(&s->pb, 16, 0);
    put_bits(&s->pb, 16, VISUAL_OBJ_STARTCODE);

    put_bits(&s->pb, 1, 1);
    put_bits(&s->pb, 4, vo_ver_id);
    put_bits(&s->pb, 3, 1);     // priority

    put_bits(&s->pb, 4, 1);     // visual obj type== video obj

    put_bits(&s->pb, 1, 0);     // video signal type == no clue // FIXME

    ff_mpeg4_stuffing(&s->pb);
}