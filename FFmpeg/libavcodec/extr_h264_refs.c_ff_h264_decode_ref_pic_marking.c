#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {scalar_t__ type; } ;
struct TYPE_8__ {int explicit_ref_marking; int curr_pic_num; int max_pic_num; int nb_mmco; TYPE_1__* mmco; } ;
struct TYPE_7__ {unsigned int long_arg; int short_pic_num; scalar_t__ opcode; } ;
typedef  scalar_t__ MMCOOpcode ;
typedef  TYPE_1__ MMCO ;
typedef  TYPE_2__ H264SliceContext ;
typedef  TYPE_3__ H2645NAL ;
typedef  int /*<<< orphan*/  GetBitContext ;

/* Variables and functions */
 int /*<<< orphan*/  AV_LOG_ERROR ; 
 scalar_t__ FIELD_PICTURE (TYPE_2__*) ; 
 scalar_t__ H264_NAL_IDR_SLICE ; 
 int MAX_MMCO_COUNT ; 
 scalar_t__ MMCO_END ; 
 scalar_t__ MMCO_LONG ; 
 scalar_t__ MMCO_LONG2UNUSED ; 
 scalar_t__ MMCO_SET_MAX_LONG ; 
 scalar_t__ MMCO_SHORT2LONG ; 
 scalar_t__ MMCO_SHORT2UNUSED ; 
 int /*<<< orphan*/  av_log (void*,int /*<<< orphan*/ ,char*,scalar_t__) ; 
 int get_bits1 (int /*<<< orphan*/ *) ; 
 void* get_ue_golomb_31 (int /*<<< orphan*/ *) ; 
 int get_ue_golomb_long (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  skip_bits1 (int /*<<< orphan*/ *) ; 

int ff_h264_decode_ref_pic_marking(H264SliceContext *sl, GetBitContext *gb,
                                   const H2645NAL *nal, void *logctx)
{
    int i;
    MMCO *mmco = sl->mmco;
    int nb_mmco = 0;

    if (nal->type == H264_NAL_IDR_SLICE) { // FIXME fields
        skip_bits1(gb); // broken_link
        if (get_bits1(gb)) {
            mmco[0].opcode   = MMCO_LONG;
            mmco[0].long_arg = 0;
            nb_mmco          = 1;
        }
        sl->explicit_ref_marking = 1;
    } else {
        sl->explicit_ref_marking = get_bits1(gb);
        if (sl->explicit_ref_marking) {
            for (i = 0; i < MAX_MMCO_COUNT; i++) {
                MMCOOpcode opcode = get_ue_golomb_31(gb);

                mmco[i].opcode = opcode;
                if (opcode == MMCO_SHORT2UNUSED || opcode == MMCO_SHORT2LONG) {
                    mmco[i].short_pic_num =
                        (sl->curr_pic_num - get_ue_golomb_long(gb) - 1) &
                            (sl->max_pic_num - 1);
                }
                if (opcode == MMCO_SHORT2LONG || opcode == MMCO_LONG2UNUSED ||
                    opcode == MMCO_LONG || opcode == MMCO_SET_MAX_LONG) {
                    unsigned int long_arg = get_ue_golomb_31(gb);
                    if (long_arg >= 32 ||
                        (long_arg >= 16 && !(opcode == MMCO_SET_MAX_LONG &&
                                             long_arg == 16) &&
                         !(opcode == MMCO_LONG2UNUSED && FIELD_PICTURE(sl)))) {
                        av_log(logctx, AV_LOG_ERROR,
                               "illegal long ref in memory management control "
                               "operation %d\n", opcode);
                        sl->nb_mmco = i;
                        return -1;
                    }
                    mmco[i].long_arg = long_arg;
                }

                if (opcode > (unsigned) MMCO_LONG) {
                    av_log(logctx, AV_LOG_ERROR,
                           "illegal memory management control operation %d\n",
                           opcode);
                    sl->nb_mmco = i;
                    return -1;
                }
                if (opcode == MMCO_END)
                    break;
            }
            nb_mmco = i;
        }
    }

    sl->nb_mmco = nb_mmco;

    return 0;
}