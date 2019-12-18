#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_6__ ;
typedef  struct TYPE_13__   TYPE_5__ ;
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_14__ {TYPE_1__** sps_list; } ;
struct TYPE_12__ {int /*<<< orphan*/  picture_struct; } ;
struct TYPE_13__ {size_t active_seq_parameter_set_id; TYPE_4__ picture_timing; } ;
struct TYPE_10__ {scalar_t__ frame_field_info_present_flag; } ;
struct TYPE_11__ {TYPE_2__ vui; } ;
struct TYPE_9__ {scalar_t__ data; } ;
typedef  TYPE_3__ HEVCSPS ;
typedef  TYPE_4__ HEVCSEIPictureTiming ;
typedef  TYPE_5__ HEVCSEI ;
typedef  TYPE_6__ HEVCParamSets ;
typedef  int /*<<< orphan*/  GetBitContext ;

/* Variables and functions */
 int AVERROR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  AV_LOG_DEBUG ; 
 int /*<<< orphan*/  AV_PICTURE_STRUCTURE_BOTTOM_FIELD ; 
 int /*<<< orphan*/  AV_PICTURE_STRUCTURE_TOP_FIELD ; 
 int /*<<< orphan*/  AV_PICTURE_STRUCTURE_UNKNOWN ; 
 int /*<<< orphan*/  ENOMEM ; 
 int /*<<< orphan*/  av_log (void*,int /*<<< orphan*/ ,char*) ; 
 int get_bits (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  skip_bits1 (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  skip_bits_long (int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static int decode_nal_sei_pic_timing(HEVCSEI *s, GetBitContext *gb, const HEVCParamSets *ps,
                                     void *logctx, int size)
{
    HEVCSEIPictureTiming *h = &s->picture_timing;
    HEVCSPS *sps;

    if (!ps->sps_list[s->active_seq_parameter_set_id])
        return(AVERROR(ENOMEM));
    sps = (HEVCSPS*)ps->sps_list[s->active_seq_parameter_set_id]->data;

    if (sps->vui.frame_field_info_present_flag) {
        int pic_struct = get_bits(gb, 4);
        h->picture_struct = AV_PICTURE_STRUCTURE_UNKNOWN;
        if (pic_struct == 2 || pic_struct == 10 || pic_struct == 12) {
            av_log(logctx, AV_LOG_DEBUG, "BOTTOM Field\n");
            h->picture_struct = AV_PICTURE_STRUCTURE_BOTTOM_FIELD;
        } else if (pic_struct == 1 || pic_struct == 9 || pic_struct == 11) {
            av_log(logctx, AV_LOG_DEBUG, "TOP Field\n");
            h->picture_struct = AV_PICTURE_STRUCTURE_TOP_FIELD;
        }
        get_bits(gb, 2);                   // source_scan_type
        get_bits(gb, 1);                   // duplicate_flag
        skip_bits1(gb);
        size--;
    }
    skip_bits_long(gb, 8 * size);

    return 0;
}