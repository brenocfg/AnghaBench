#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  intra_types ;
typedef  scalar_t__ int8_t ;
struct TYPE_12__ {int mb_x; int mb_y; int mb_stride; scalar_t__ pict_type; TYPE_1__* current_picture_ptr; int /*<<< orphan*/  gb; } ;
struct TYPE_10__ {int /*<<< orphan*/  vlc_set; int /*<<< orphan*/  quant; } ;
struct TYPE_11__ {int block_type; int (* decode_mb_info ) (TYPE_3__*) ;size_t* mb_type; int is16; int intra_types_stride; int chroma_vlc; int luma_vlc; scalar_t__ (* decode_intra_types ) (TYPE_3__*,int /*<<< orphan*/ *,scalar_t__*) ;void* cur_vlcs; TYPE_2__ si; TYPE_4__ s; } ;
struct TYPE_9__ {int /*<<< orphan*/ * mb_type; } ;
typedef  TYPE_3__ RV34DecContext ;
typedef  TYPE_4__ MpegEncContext ;
typedef  int /*<<< orphan*/  GetBitContext ;

/* Variables and functions */
 scalar_t__ AV_PICTURE_TYPE_B ; 
 scalar_t__ AV_PICTURE_TYPE_P ; 
 scalar_t__ IS_INTRA (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IS_INTRA16x16 (int /*<<< orphan*/ ) ; 
 size_t RV34_MB_B_DIRECT ; 
 size_t RV34_MB_P_16x16 ; 
 size_t RV34_MB_P_MIX16x16 ; 
 size_t RV34_MB_SKIP ; 
 void* choose_vlc_set (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  fill_rectangle (scalar_t__*,int,int,int,int,int) ; 
 int get_bits (int /*<<< orphan*/ *,int) ; 
 int rv34_decode_cbp (int /*<<< orphan*/ *,void*,int) ; 
 scalar_t__ rv34_decode_mv (TYPE_3__*,size_t) ; 
 int /*<<< orphan*/ * rv34_mb_type_to_lavc ; 
 int stub1 (TYPE_3__*) ; 
 scalar_t__ stub2 (TYPE_3__*,int /*<<< orphan*/ *,scalar_t__*) ; 

__attribute__((used)) static int rv34_decode_inter_mb_header(RV34DecContext *r, int8_t *intra_types)
{
    MpegEncContext *s = &r->s;
    GetBitContext *gb = &s->gb;
    int mb_pos = s->mb_x + s->mb_y * s->mb_stride;
    int i, t;

    r->block_type = r->decode_mb_info(r);
    if(r->block_type == -1)
        return -1;
    s->current_picture_ptr->mb_type[mb_pos] = rv34_mb_type_to_lavc[r->block_type];
    r->mb_type[mb_pos] = r->block_type;
    if(r->block_type == RV34_MB_SKIP){
        if(s->pict_type == AV_PICTURE_TYPE_P)
            r->mb_type[mb_pos] = RV34_MB_P_16x16;
        if(s->pict_type == AV_PICTURE_TYPE_B)
            r->mb_type[mb_pos] = RV34_MB_B_DIRECT;
    }
    r->is16 = !!IS_INTRA16x16(s->current_picture_ptr->mb_type[mb_pos]);
    if (rv34_decode_mv(r, r->block_type) < 0)
        return -1;
    if(r->block_type == RV34_MB_SKIP){
        fill_rectangle(intra_types, 4, 4, r->intra_types_stride, 0, sizeof(intra_types[0]));
        return 0;
    }
    r->chroma_vlc = 1;
    r->luma_vlc   = 0;

    if(IS_INTRA(s->current_picture_ptr->mb_type[mb_pos])){
        if(r->is16){
            t = get_bits(gb, 2);
            fill_rectangle(intra_types, 4, 4, r->intra_types_stride, t, sizeof(intra_types[0]));
            r->luma_vlc   = 2;
        }else{
            if(r->decode_intra_types(r, gb, intra_types) < 0)
                return -1;
            r->luma_vlc   = 1;
        }
        r->chroma_vlc = 0;
        r->cur_vlcs = choose_vlc_set(r->si.quant, r->si.vlc_set, 0);
    }else{
        for(i = 0; i < 16; i++)
            intra_types[(i & 3) + (i>>2) * r->intra_types_stride] = 0;
        r->cur_vlcs = choose_vlc_set(r->si.quant, r->si.vlc_set, 1);
        if(r->mb_type[mb_pos] == RV34_MB_P_MIX16x16){
            r->is16 = 1;
            r->chroma_vlc = 1;
            r->luma_vlc   = 2;
            r->cur_vlcs = choose_vlc_set(r->si.quant, r->si.vlc_set, 0);
        }
    }

    return rv34_decode_cbp(gb, r->cur_vlcs, r->is16);
}