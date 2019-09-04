#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int /*<<< orphan*/  kstate ;
struct TYPE_7__ {scalar_t__ last_htaps; scalar_t__ last_diag_mc; scalar_t__ htaps; scalar_t__ diag_mc; int /*<<< orphan*/ * hcoeff; int /*<<< orphan*/ * last_hcoeff; } ;
struct TYPE_6__ {int keyframe; int always_reset; int last_spatial_decomposition_type; int last_qlog; int last_qbias; int last_mv_scale; int last_block_max_depth; int version; int temporal_decomposition_type; int temporal_decomposition_count; int spatial_decomposition_count; int colorspace_type; int nb_planes; int chroma_h_shift; int chroma_v_shift; int spatial_scalability; int max_ref_frames; scalar_t__ last_spatial_decomposition_count; int spatial_decomposition_type; int qlog; int mv_scale; int qbias; int block_max_depth; int /*<<< orphan*/ * header_state; int /*<<< orphan*/  c; TYPE_2__* plane; } ;
typedef  TYPE_1__ SnowContext ;
typedef  TYPE_2__ Plane ;

/* Variables and functions */
 int FFABS (int /*<<< orphan*/ ) ; 
 int FFMIN (int,int) ; 
 int /*<<< orphan*/  MID_STATE ; 
 int /*<<< orphan*/  encode_qlogs (TYPE_1__*) ; 
 int /*<<< orphan*/  ff_snow_reset_contexts (TYPE_1__*) ; 
 int /*<<< orphan*/  memcmp (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  put_rac (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  put_symbol (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int,int) ; 

__attribute__((used)) static void encode_header(SnowContext *s){
    int plane_index, i;
    uint8_t kstate[32];

    memset(kstate, MID_STATE, sizeof(kstate));

    put_rac(&s->c, kstate, s->keyframe);
    if(s->keyframe || s->always_reset){
        ff_snow_reset_contexts(s);
        s->last_spatial_decomposition_type=
        s->last_qlog=
        s->last_qbias=
        s->last_mv_scale=
        s->last_block_max_depth= 0;
        for(plane_index=0; plane_index<2; plane_index++){
            Plane *p= &s->plane[plane_index];
            p->last_htaps=0;
            p->last_diag_mc=0;
            memset(p->last_hcoeff, 0, sizeof(p->last_hcoeff));
        }
    }
    if(s->keyframe){
        put_symbol(&s->c, s->header_state, s->version, 0);
        put_rac(&s->c, s->header_state, s->always_reset);
        put_symbol(&s->c, s->header_state, s->temporal_decomposition_type, 0);
        put_symbol(&s->c, s->header_state, s->temporal_decomposition_count, 0);
        put_symbol(&s->c, s->header_state, s->spatial_decomposition_count, 0);
        put_symbol(&s->c, s->header_state, s->colorspace_type, 0);
        if (s->nb_planes > 2) {
            put_symbol(&s->c, s->header_state, s->chroma_h_shift, 0);
            put_symbol(&s->c, s->header_state, s->chroma_v_shift, 0);
        }
        put_rac(&s->c, s->header_state, s->spatial_scalability);
//        put_rac(&s->c, s->header_state, s->rate_scalability);
        put_symbol(&s->c, s->header_state, s->max_ref_frames-1, 0);

        encode_qlogs(s);
    }

    if(!s->keyframe){
        int update_mc=0;
        for(plane_index=0; plane_index<FFMIN(s->nb_planes, 2); plane_index++){
            Plane *p= &s->plane[plane_index];
            update_mc |= p->last_htaps   != p->htaps;
            update_mc |= p->last_diag_mc != p->diag_mc;
            update_mc |= !!memcmp(p->last_hcoeff, p->hcoeff, sizeof(p->hcoeff));
        }
        put_rac(&s->c, s->header_state, update_mc);
        if(update_mc){
            for(plane_index=0; plane_index<FFMIN(s->nb_planes, 2); plane_index++){
                Plane *p= &s->plane[plane_index];
                put_rac(&s->c, s->header_state, p->diag_mc);
                put_symbol(&s->c, s->header_state, p->htaps/2-1, 0);
                for(i= p->htaps/2; i; i--)
                    put_symbol(&s->c, s->header_state, FFABS(p->hcoeff[i]), 0);
            }
        }
        if(s->last_spatial_decomposition_count != s->spatial_decomposition_count){
            put_rac(&s->c, s->header_state, 1);
            put_symbol(&s->c, s->header_state, s->spatial_decomposition_count, 0);
            encode_qlogs(s);
        }else
            put_rac(&s->c, s->header_state, 0);
    }

    put_symbol(&s->c, s->header_state, s->spatial_decomposition_type - s->last_spatial_decomposition_type, 1);
    put_symbol(&s->c, s->header_state, s->qlog            - s->last_qlog    , 1);
    put_symbol(&s->c, s->header_state, s->mv_scale        - s->last_mv_scale, 1);
    put_symbol(&s->c, s->header_state, s->qbias           - s->last_qbias   , 1);
    put_symbol(&s->c, s->header_state, s->block_max_depth - s->last_block_max_depth, 1);

}