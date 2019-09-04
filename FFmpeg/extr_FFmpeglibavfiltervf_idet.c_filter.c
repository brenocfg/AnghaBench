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
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int int64_t ;
typedef  scalar_t__ Type ;
struct TYPE_14__ {TYPE_5__* priv; } ;
struct TYPE_13__ {int interlace_threshold; int progressive_threshold; int repeat_threshold; scalar_t__* history; scalar_t__ last_type; void** poststat; void** prestat; void** repeats; int /*<<< orphan*/ * total_poststat; int /*<<< orphan*/ * total_prestat; int /*<<< orphan*/ * total_repeats; int /*<<< orphan*/  decay_coefficient; TYPE_3__* cur; scalar_t__ (* filter_line ) (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ;TYPE_4__* next; TYPE_2__* prev; TYPE_1__* csp; } ;
struct TYPE_12__ {int /*<<< orphan*/ ** data; } ;
struct TYPE_11__ {int width; int height; int* linesize; int top_field_first; int interlaced_frame; int /*<<< orphan*/ ** data; int /*<<< orphan*/ * metadata; } ;
struct TYPE_10__ {int /*<<< orphan*/ ** data; } ;
struct TYPE_9__ {int nb_components; int /*<<< orphan*/  log2_chroma_h; int /*<<< orphan*/  log2_chroma_w; } ;
typedef  size_t RepeatedField ;
typedef  TYPE_5__ IDETContext ;
typedef  TYPE_6__ AVFilterContext ;
typedef  int /*<<< orphan*/  AVDictionary ;

/* Variables and functions */
 int AV_CEIL_RSHIFT (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  AV_LOG_DEBUG ; 
 size_t BFF ; 
 int HIST_SIZE ; 
 scalar_t__ PRECISION ; 
 size_t PROGRESSIVE ; 
 size_t REPEAT_BOTTOM ; 
 size_t REPEAT_NONE ; 
 size_t REPEAT_TOP ; 
 size_t TFF ; 
 scalar_t__ UNDETERMINED ; 
 int /*<<< orphan*/  av_dict_set (int /*<<< orphan*/ **,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  av_dict_set_fxp (int /*<<< orphan*/ **,char*,void*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  av_log (TYPE_6__*,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 void* av_rescale (void*,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  memmove (scalar_t__*,scalar_t__*,int) ; 
 int /*<<< orphan*/  rep2str (size_t) ; 
 scalar_t__ stub1 (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 scalar_t__ stub2 (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 scalar_t__ stub3 (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 scalar_t__ stub4 (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  type2str (scalar_t__) ; 

__attribute__((used)) static void filter(AVFilterContext *ctx)
{
    IDETContext *idet = ctx->priv;
    int y, i;
    int64_t alpha[2]={0};
    int64_t delta=0;
    int64_t gamma[2]={0};
    Type type, best_type;
    RepeatedField repeat;
    int match = 0;
    AVDictionary **metadata = &idet->cur->metadata;

    for (i = 0; i < idet->csp->nb_components; i++) {
        int w = idet->cur->width;
        int h = idet->cur->height;
        int refs = idet->cur->linesize[i];

        if (i && i<3) {
            w = AV_CEIL_RSHIFT(w, idet->csp->log2_chroma_w);
            h = AV_CEIL_RSHIFT(h, idet->csp->log2_chroma_h);
        }

        for (y = 2; y < h - 2; y++) {
            uint8_t *prev = &idet->prev->data[i][y*refs];
            uint8_t *cur  = &idet->cur ->data[i][y*refs];
            uint8_t *next = &idet->next->data[i][y*refs];
            alpha[ y   &1] += idet->filter_line(cur-refs, prev, cur+refs, w);
            alpha[(y^1)&1] += idet->filter_line(cur-refs, next, cur+refs, w);
            delta          += idet->filter_line(cur-refs,  cur, cur+refs, w);
            gamma[(y^1)&1] += idet->filter_line(cur     , prev, cur     , w);
        }
    }

    if      (alpha[0] > idet->interlace_threshold * alpha[1]){
        type = TFF;
    }else if(alpha[1] > idet->interlace_threshold * alpha[0]){
        type = BFF;
    }else if(alpha[1] > idet->progressive_threshold * delta){
        type = PROGRESSIVE;
    }else{
        type = UNDETERMINED;
    }

    if ( gamma[0] > idet->repeat_threshold * gamma[1] ){
        repeat = REPEAT_TOP;
    } else if ( gamma[1] > idet->repeat_threshold * gamma[0] ){
        repeat = REPEAT_BOTTOM;
    } else {
        repeat = REPEAT_NONE;
    }

    memmove(idet->history+1, idet->history, HIST_SIZE-1);
    idet->history[0] = type;
    best_type = UNDETERMINED;
    for(i=0; i<HIST_SIZE; i++){
        if(idet->history[i] != UNDETERMINED){
            if(best_type == UNDETERMINED)
                best_type = idet->history[i];

            if(idet->history[i] == best_type) {
                match++;
            }else{
                match=0;
                break;
            }
        }
    }
    if(idet->last_type == UNDETERMINED){
        if(match  ) idet->last_type = best_type;
    }else{
        if(match>2) idet->last_type = best_type;
    }

    if      (idet->last_type == TFF){
        idet->cur->top_field_first = 1;
        idet->cur->interlaced_frame = 1;
    }else if(idet->last_type == BFF){
        idet->cur->top_field_first = 0;
        idet->cur->interlaced_frame = 1;
    }else if(idet->last_type == PROGRESSIVE){
        idet->cur->interlaced_frame = 0;
    }

    for(i=0; i<3; i++)
        idet->repeats[i]  = av_rescale(idet->repeats [i], idet->decay_coefficient, PRECISION);

    for(i=0; i<4; i++){
        idet->prestat [i] = av_rescale(idet->prestat [i], idet->decay_coefficient, PRECISION);
        idet->poststat[i] = av_rescale(idet->poststat[i], idet->decay_coefficient, PRECISION);
    }

    idet->total_repeats [         repeat] ++;
    idet->repeats       [         repeat] += PRECISION;

    idet->total_prestat [           type] ++;
    idet->prestat       [           type] += PRECISION;

    idet->total_poststat[idet->last_type] ++;
    idet->poststat      [idet->last_type] += PRECISION;

    av_log(ctx, AV_LOG_DEBUG, "Repeated Field:%12s, Single frame:%12s, Multi frame:%12s\n",
           rep2str(repeat), type2str(type), type2str(idet->last_type));

    av_dict_set    (metadata, "lavfi.idet.repeated.current_frame", rep2str(repeat), 0);
    av_dict_set_fxp(metadata, "lavfi.idet.repeated.neither",       idet->repeats[REPEAT_NONE], 2, 0);
    av_dict_set_fxp(metadata, "lavfi.idet.repeated.top",           idet->repeats[REPEAT_TOP], 2, 0);
    av_dict_set_fxp(metadata, "lavfi.idet.repeated.bottom",        idet->repeats[REPEAT_BOTTOM], 2, 0);

    av_dict_set    (metadata, "lavfi.idet.single.current_frame",   type2str(type), 0);
    av_dict_set_fxp(metadata, "lavfi.idet.single.tff",             idet->prestat[TFF], 2 , 0);
    av_dict_set_fxp(metadata, "lavfi.idet.single.bff",             idet->prestat[BFF], 2, 0);
    av_dict_set_fxp(metadata, "lavfi.idet.single.progressive",     idet->prestat[PROGRESSIVE], 2, 0);
    av_dict_set_fxp(metadata, "lavfi.idet.single.undetermined",    idet->prestat[UNDETERMINED], 2, 0);

    av_dict_set    (metadata, "lavfi.idet.multiple.current_frame", type2str(idet->last_type), 0);
    av_dict_set_fxp(metadata, "lavfi.idet.multiple.tff",           idet->poststat[TFF], 2, 0);
    av_dict_set_fxp(metadata, "lavfi.idet.multiple.bff",           idet->poststat[BFF], 2, 0);
    av_dict_set_fxp(metadata, "lavfi.idet.multiple.progressive",   idet->poststat[PROGRESSIVE], 2, 0);
    av_dict_set_fxp(metadata, "lavfi.idet.multiple.undetermined",  idet->poststat[UNDETERMINED], 2, 0);
}