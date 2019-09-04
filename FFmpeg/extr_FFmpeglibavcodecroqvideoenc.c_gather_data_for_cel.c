#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_20__   TYPE_7__ ;
typedef  struct TYPE_19__   TYPE_6__ ;
typedef  struct TYPE_18__   TYPE_5__ ;
typedef  struct TYPE_17__   TYPE_4__ ;
typedef  struct TYPE_16__   TYPE_3__ ;
typedef  struct TYPE_15__   TYPE_2__ ;
typedef  struct TYPE_14__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
struct TYPE_20__ {size_t best_coding; size_t cbEntry; size_t* subCels; scalar_t__ best_bit_use; scalar_t__* eval_dist; } ;
struct TYPE_19__ {int /*<<< orphan*/  linesize; int /*<<< orphan*/  data; } ;
struct TYPE_18__ {int sourceY; int sourceX; int* eval_dist; size_t cbEntry; int best_coding; TYPE_7__* subCels; int /*<<< orphan*/  motion; } ;
struct TYPE_17__ {int width; int framesSinceKeyframe; int lambda; TYPE_6__* frame_to_enc; TYPE_1__* current_frame; int /*<<< orphan*/ * this_motion8; } ;
struct TYPE_15__ {int /*<<< orphan*/ * usedCB2; int /*<<< orphan*/ * usedCB4; int /*<<< orphan*/  numCB4; int /*<<< orphan*/  unpacked_cb4_enlarged; } ;
struct TYPE_16__ {int mainChunkSize; TYPE_2__ codebooks; int /*<<< orphan*/ * used_option; } ;
struct TYPE_14__ {int /*<<< orphan*/  linesize; int /*<<< orphan*/  data; } ;
typedef  TYPE_3__ RoqTempdata ;
typedef  TYPE_4__ RoqContext ;
typedef  TYPE_5__ CelEvaluation ;

/* Variables and functions */
 void* INT_MAX ; 
 int ROQ_LAMBDA_SCALE ; 
 size_t RoQ_ID_CCC ; 
 size_t RoQ_ID_FCC ; 
 size_t RoQ_ID_MOT ; 
 size_t RoQ_ID_SLD ; 
 int block_sse (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int eval_motion_dist (TYPE_4__*,int,int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  gather_data_for_subcel (TYPE_7__*,int,int,TYPE_4__*,TYPE_3__*) ; 
 int /*<<< orphan*/  get_frame_mb (TYPE_6__*,int,int,int /*<<< orphan*/ *,int) ; 
 int index_mb (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,size_t*,int) ; 

__attribute__((used)) static void gather_data_for_cel(CelEvaluation *cel, RoqContext *enc,
                                RoqTempdata *tempData)
{
    uint8_t mb8[8*8*3];
    int index = cel->sourceY*enc->width/64 + cel->sourceX/8;
    int i, j, best_dist, divide_bit_use;

    int bitsUsed[4] = {2, 10, 10, 0};

    if (enc->framesSinceKeyframe >= 1) {
        cel->motion = enc->this_motion8[index];

        cel->eval_dist[RoQ_ID_FCC] =
            eval_motion_dist(enc, cel->sourceX, cel->sourceY,
                             enc->this_motion8[index], 8);
    } else
        cel->eval_dist[RoQ_ID_FCC] = INT_MAX;

    if (enc->framesSinceKeyframe >= 2)
        cel->eval_dist[RoQ_ID_MOT] = block_sse(enc->frame_to_enc->data,
                                               enc->current_frame->data,
                                               cel->sourceX, cel->sourceY,
                                               cel->sourceX, cel->sourceY,
                                               enc->frame_to_enc->linesize,
                                               enc->current_frame->linesize,8);
    else
        cel->eval_dist[RoQ_ID_MOT] = INT_MAX;

    get_frame_mb(enc->frame_to_enc, cel->sourceX, cel->sourceY, mb8, 8);

    cel->eval_dist[RoQ_ID_SLD] =
        index_mb(mb8, tempData->codebooks.unpacked_cb4_enlarged,
                 tempData->codebooks.numCB4, &cel->cbEntry, 8);

    gather_data_for_subcel(cel->subCels + 0, cel->sourceX+0, cel->sourceY+0, enc, tempData);
    gather_data_for_subcel(cel->subCels + 1, cel->sourceX+4, cel->sourceY+0, enc, tempData);
    gather_data_for_subcel(cel->subCels + 2, cel->sourceX+0, cel->sourceY+4, enc, tempData);
    gather_data_for_subcel(cel->subCels + 3, cel->sourceX+4, cel->sourceY+4, enc, tempData);

    cel->eval_dist[RoQ_ID_CCC] = 0;
    divide_bit_use = 0;
    for (i=0; i<4; i++) {
        cel->eval_dist[RoQ_ID_CCC] +=
            cel->subCels[i].eval_dist[cel->subCels[i].best_coding];
        divide_bit_use += cel->subCels[i].best_bit_use;
    }

    best_dist = INT_MAX;
    bitsUsed[3] = 2 + divide_bit_use;

    for (i=0; i<4; i++)
        if (ROQ_LAMBDA_SCALE*cel->eval_dist[i] + enc->lambda*bitsUsed[i] <
            best_dist) {
            cel->best_coding = i;
            best_dist = ROQ_LAMBDA_SCALE*cel->eval_dist[i] +
                enc->lambda*bitsUsed[i];
        }

    tempData->used_option[cel->best_coding]++;
    tempData->mainChunkSize += bitsUsed[cel->best_coding];

    if (cel->best_coding == RoQ_ID_SLD)
        tempData->codebooks.usedCB4[cel->cbEntry]++;

    if (cel->best_coding == RoQ_ID_CCC)
        for (i=0; i<4; i++) {
            if (cel->subCels[i].best_coding == RoQ_ID_SLD)
                tempData->codebooks.usedCB4[cel->subCels[i].cbEntry]++;
            else if (cel->subCels[i].best_coding == RoQ_ID_CCC)
                for (j=0; j<4; j++)
                    tempData->codebooks.usedCB2[cel->subCels[i].subCels[j]]++;
        }
}