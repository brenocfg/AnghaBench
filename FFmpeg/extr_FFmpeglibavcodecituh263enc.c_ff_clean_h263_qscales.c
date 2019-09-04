#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int int8_t ;
struct TYPE_5__ {int* qscale_table; } ;
struct TYPE_6__ {int mb_num; size_t* mb_index2xy; scalar_t__ codec_id; int* mb_type; TYPE_1__ current_picture; } ;
typedef  TYPE_2__ MpegEncContext ;

/* Variables and functions */
 scalar_t__ AV_CODEC_ID_H263P ; 
 int CANDIDATE_MB_TYPE_INTER ; 
 int CANDIDATE_MB_TYPE_INTER4V ; 
 int /*<<< orphan*/  ff_init_qscale_tab (TYPE_2__*) ; 

void ff_clean_h263_qscales(MpegEncContext *s){
    int i;
    int8_t * const qscale_table = s->current_picture.qscale_table;

    ff_init_qscale_tab(s);

    for(i=1; i<s->mb_num; i++){
        if(qscale_table[ s->mb_index2xy[i] ] - qscale_table[ s->mb_index2xy[i-1] ] >2)
            qscale_table[ s->mb_index2xy[i] ]= qscale_table[ s->mb_index2xy[i-1] ]+2;
    }
    for(i=s->mb_num-2; i>=0; i--){
        if(qscale_table[ s->mb_index2xy[i] ] - qscale_table[ s->mb_index2xy[i+1] ] >2)
            qscale_table[ s->mb_index2xy[i] ]= qscale_table[ s->mb_index2xy[i+1] ]+2;
    }

    if(s->codec_id != AV_CODEC_ID_H263P){
        for(i=1; i<s->mb_num; i++){
            int mb_xy= s->mb_index2xy[i];

            if(qscale_table[mb_xy] != qscale_table[s->mb_index2xy[i-1]] && (s->mb_type[mb_xy]&CANDIDATE_MB_TYPE_INTER4V)){
                s->mb_type[mb_xy]|= CANDIDATE_MB_TYPE_INTER;
            }
        }
    }
}