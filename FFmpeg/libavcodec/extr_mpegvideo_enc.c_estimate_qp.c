#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_16__   TYPE_5__ ;
typedef  struct TYPE_15__   TYPE_4__ ;
typedef  struct TYPE_14__   TYPE_3__ ;
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
struct TYPE_15__ {TYPE_3__* f; } ;
struct TYPE_16__ {int next_lambda; int codec_id; int lambda; int* lambda_table; TYPE_4__ current_picture; scalar_t__ adaptive_quant; TYPE_2__* current_picture_ptr; int /*<<< orphan*/  fixed_qscale; } ;
struct TYPE_14__ {int quality; } ;
struct TYPE_13__ {TYPE_1__* f; } ;
struct TYPE_12__ {int quality; } ;
typedef  TYPE_5__ MpegEncContext ;

/* Variables and functions */
#define  AV_CODEC_ID_FLV1 131 
#define  AV_CODEC_ID_H263 130 
#define  AV_CODEC_ID_H263P 129 
#define  AV_CODEC_ID_MPEG4 128 
 int /*<<< orphan*/  CONFIG_H263_ENCODER ; 
 int /*<<< orphan*/  CONFIG_MPEG4_ENCODER ; 
 int /*<<< orphan*/  ff_clean_h263_qscales (TYPE_5__*) ; 
 int /*<<< orphan*/  ff_clean_mpeg4_qscales (TYPE_5__*) ; 
 int /*<<< orphan*/  ff_init_qscale_tab (TYPE_5__*) ; 
 int ff_rate_estimate_qscale (TYPE_5__*,int) ; 
 int /*<<< orphan*/  update_qscale (TYPE_5__*) ; 

__attribute__((used)) static int estimate_qp(MpegEncContext *s, int dry_run){
    if (s->next_lambda){
        s->current_picture_ptr->f->quality =
        s->current_picture.f->quality = s->next_lambda;
        if(!dry_run) s->next_lambda= 0;
    } else if (!s->fixed_qscale) {
        int quality = ff_rate_estimate_qscale(s, dry_run);
        s->current_picture_ptr->f->quality =
        s->current_picture.f->quality = quality;
        if (s->current_picture.f->quality < 0)
            return -1;
    }

    if(s->adaptive_quant){
        switch(s->codec_id){
        case AV_CODEC_ID_MPEG4:
            if (CONFIG_MPEG4_ENCODER)
                ff_clean_mpeg4_qscales(s);
            break;
        case AV_CODEC_ID_H263:
        case AV_CODEC_ID_H263P:
        case AV_CODEC_ID_FLV1:
            if (CONFIG_H263_ENCODER)
                ff_clean_h263_qscales(s);
            break;
        default:
            ff_init_qscale_tab(s);
        }

        s->lambda= s->lambda_table[0];
        //FIXME broken
    }else
        s->lambda = s->current_picture.f->quality;
    update_qscale(s);
    return 0;
}