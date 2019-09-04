#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int uint8_t ;
typedef  int motion_fy ;
typedef  int motion_fx ;
typedef  int motion_bx ;
typedef  int int8_t ;
struct TYPE_8__ {int sub_flags; int const xmin; int const ymin; int const xmax; int const ymax; } ;
struct TYPE_7__ {int mb_stride; int** b_bidir_forw_mv_table; int** b_bidir_back_mv_table; int** b_forw_mv_table; int** b_back_mv_table; TYPE_1__* avctx; TYPE_3__ me; } ;
struct TYPE_6__ {size_t bidir_refine; } ;
typedef  TYPE_2__ MpegEncContext ;
typedef  TYPE_3__ MotionEstContext ;

/* Variables and functions */
 int const FFMAX (int,int) ; 
 int const FFMIN (int const,int const) ; 
 int const FLAG_QPEL ; 
 int check_bidir_mv (TYPE_2__*,int,int,int,int,int,int,int,int,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static inline int bidir_refine(MpegEncContext * s, int mb_x, int mb_y)
{
    MotionEstContext * const c= &s->me;
    const int mot_stride = s->mb_stride;
    const int xy = mb_y *mot_stride + mb_x;
    int fbmin;
    int pred_fx= s->b_bidir_forw_mv_table[xy-1][0];
    int pred_fy= s->b_bidir_forw_mv_table[xy-1][1];
    int pred_bx= s->b_bidir_back_mv_table[xy-1][0];
    int pred_by= s->b_bidir_back_mv_table[xy-1][1];
    int motion_fx= s->b_bidir_forw_mv_table[xy][0]= s->b_forw_mv_table[xy][0];
    int motion_fy= s->b_bidir_forw_mv_table[xy][1]= s->b_forw_mv_table[xy][1];
    int motion_bx= s->b_bidir_back_mv_table[xy][0]= s->b_back_mv_table[xy][0];
    int motion_by= s->b_bidir_back_mv_table[xy][1]= s->b_back_mv_table[xy][1];
    const int flags= c->sub_flags;
    const int qpel= flags&FLAG_QPEL;
    const int shift= 1+qpel;
    const int xmin= c->xmin<<shift;
    const int ymin= c->ymin<<shift;
    const int xmax= c->xmax<<shift;
    const int ymax= c->ymax<<shift;
#define HASH(fx,fy,bx,by) ((fx)+17*(fy)+63*(bx)+117*(by))
#define HASH8(fx,fy,bx,by) ((uint8_t)HASH(fx,fy,bx,by))
    int hashidx= HASH(motion_fx,motion_fy, motion_bx, motion_by);
    uint8_t map[256] = { 0 };

    map[hashidx&255] = 1;

    fbmin= check_bidir_mv(s, motion_fx, motion_fy,
                          motion_bx, motion_by,
                          pred_fx, pred_fy,
                          pred_bx, pred_by,
                          0, 16);

    if(s->avctx->bidir_refine){
        int end;
        static const uint8_t limittab[5]={0,8,32,64,80};
        const int limit= limittab[s->avctx->bidir_refine];
        static const int8_t vect[][4]={
{ 0, 0, 0, 1}, { 0, 0, 0,-1}, { 0, 0, 1, 0}, { 0, 0,-1, 0}, { 0, 1, 0, 0}, { 0,-1, 0, 0}, { 1, 0, 0, 0}, {-1, 0, 0, 0},

{ 0, 0, 1, 1}, { 0, 0,-1,-1}, { 0, 1, 1, 0}, { 0,-1,-1, 0}, { 1, 1, 0, 0}, {-1,-1, 0, 0}, { 1, 0, 0, 1}, {-1, 0, 0,-1},
{ 0, 1, 0, 1}, { 0,-1, 0,-1}, { 1, 0, 1, 0}, {-1, 0,-1, 0},
{ 0, 0,-1, 1}, { 0, 0, 1,-1}, { 0,-1, 1, 0}, { 0, 1,-1, 0}, {-1, 1, 0, 0}, { 1,-1, 0, 0}, { 1, 0, 0,-1}, {-1, 0, 0, 1},
{ 0,-1, 0, 1}, { 0, 1, 0,-1}, {-1, 0, 1, 0}, { 1, 0,-1, 0},

{ 0, 1, 1, 1}, { 0,-1,-1,-1}, { 1, 1, 1, 0}, {-1,-1,-1, 0}, { 1, 1, 0, 1}, {-1,-1, 0,-1}, { 1, 0, 1, 1}, {-1, 0,-1,-1},
{ 0,-1, 1, 1}, { 0, 1,-1,-1}, {-1, 1, 1, 0}, { 1,-1,-1, 0}, { 1, 1, 0,-1}, {-1,-1, 0, 1}, { 1, 0,-1, 1}, {-1, 0, 1,-1},
{ 0, 1,-1, 1}, { 0,-1, 1,-1}, { 1,-1, 1, 0}, {-1, 1,-1, 0}, {-1, 1, 0, 1}, { 1,-1, 0,-1}, { 1, 0, 1,-1}, {-1, 0,-1, 1},
{ 0, 1, 1,-1}, { 0,-1,-1, 1}, { 1, 1,-1, 0}, {-1,-1, 1, 0}, { 1,-1, 0, 1}, {-1, 1, 0,-1}, {-1, 0, 1, 1}, { 1, 0,-1,-1},

{ 1, 1, 1, 1}, {-1,-1,-1,-1},
{ 1, 1, 1,-1}, {-1,-1,-1, 1}, { 1, 1,-1, 1}, {-1,-1, 1,-1}, { 1,-1, 1, 1}, {-1, 1,-1,-1}, {-1, 1, 1, 1}, { 1,-1,-1,-1},
{ 1, 1,-1,-1}, {-1,-1, 1, 1}, { 1,-1,-1, 1}, {-1, 1, 1,-1}, { 1,-1, 1,-1}, {-1, 1,-1, 1},
        };
        static const uint8_t hash[]={
HASH8( 0, 0, 0, 1), HASH8( 0, 0, 0,-1), HASH8( 0, 0, 1, 0), HASH8( 0, 0,-1, 0), HASH8( 0, 1, 0, 0), HASH8( 0,-1, 0, 0), HASH8( 1, 0, 0, 0), HASH8(-1, 0, 0, 0),

HASH8( 0, 0, 1, 1), HASH8( 0, 0,-1,-1), HASH8( 0, 1, 1, 0), HASH8( 0,-1,-1, 0), HASH8( 1, 1, 0, 0), HASH8(-1,-1, 0, 0), HASH8( 1, 0, 0, 1), HASH8(-1, 0, 0,-1),
HASH8( 0, 1, 0, 1), HASH8( 0,-1, 0,-1), HASH8( 1, 0, 1, 0), HASH8(-1, 0,-1, 0),
HASH8( 0, 0,-1, 1), HASH8( 0, 0, 1,-1), HASH8( 0,-1, 1, 0), HASH8( 0, 1,-1, 0), HASH8(-1, 1, 0, 0), HASH8( 1,-1, 0, 0), HASH8( 1, 0, 0,-1), HASH8(-1, 0, 0, 1),
HASH8( 0,-1, 0, 1), HASH8( 0, 1, 0,-1), HASH8(-1, 0, 1, 0), HASH8( 1, 0,-1, 0),

HASH8( 0, 1, 1, 1), HASH8( 0,-1,-1,-1), HASH8( 1, 1, 1, 0), HASH8(-1,-1,-1, 0), HASH8( 1, 1, 0, 1), HASH8(-1,-1, 0,-1), HASH8( 1, 0, 1, 1), HASH8(-1, 0,-1,-1),
HASH8( 0,-1, 1, 1), HASH8( 0, 1,-1,-1), HASH8(-1, 1, 1, 0), HASH8( 1,-1,-1, 0), HASH8( 1, 1, 0,-1), HASH8(-1,-1, 0, 1), HASH8( 1, 0,-1, 1), HASH8(-1, 0, 1,-1),
HASH8( 0, 1,-1, 1), HASH8( 0,-1, 1,-1), HASH8( 1,-1, 1, 0), HASH8(-1, 1,-1, 0), HASH8(-1, 1, 0, 1), HASH8( 1,-1, 0,-1), HASH8( 1, 0, 1,-1), HASH8(-1, 0,-1, 1),
HASH8( 0, 1, 1,-1), HASH8( 0,-1,-1, 1), HASH8( 1, 1,-1, 0), HASH8(-1,-1, 1, 0), HASH8( 1,-1, 0, 1), HASH8(-1, 1, 0,-1), HASH8(-1, 0, 1, 1), HASH8( 1, 0,-1,-1),

HASH8( 1, 1, 1, 1), HASH8(-1,-1,-1,-1),
HASH8( 1, 1, 1,-1), HASH8(-1,-1,-1, 1), HASH8( 1, 1,-1, 1), HASH8(-1,-1, 1,-1), HASH8( 1,-1, 1, 1), HASH8(-1, 1,-1,-1), HASH8(-1, 1, 1, 1), HASH8( 1,-1,-1,-1),
HASH8( 1, 1,-1,-1), HASH8(-1,-1, 1, 1), HASH8( 1,-1,-1, 1), HASH8(-1, 1, 1,-1), HASH8( 1,-1, 1,-1), HASH8(-1, 1,-1, 1),
};

#define CHECK_BIDIR(fx,fy,bx,by)\
    if( !map[(hashidx+HASH(fx,fy,bx,by))&255]\
       &&(fx<=0 || motion_fx+fx<=xmax) && (fy<=0 || motion_fy+fy<=ymax) && (bx<=0 || motion_bx+bx<=xmax) && (by<=0 || motion_by+by<=ymax)\
       &&(fx>=0 || motion_fx+fx>=xmin) && (fy>=0 || motion_fy+fy>=ymin) && (bx>=0 || motion_bx+bx>=xmin) && (by>=0 || motion_by+by>=ymin)){\
        int score;\
        map[(hashidx+HASH(fx,fy,bx,by))&255] = 1;\
        score= check_bidir_mv(s, motion_fx+fx, motion_fy+fy, motion_bx+bx, motion_by+by, pred_fx, pred_fy, pred_bx, pred_by, 0, 16);\
        if(score < fbmin){\
            hashidx += HASH(fx,fy,bx,by);\
            fbmin= score;\
            motion_fx+=fx;\
            motion_fy+=fy;\
            motion_bx+=bx;\
            motion_by+=by;\
            end=0;\
        }\
    }
#define CHECK_BIDIR2(a,b,c,d)\
CHECK_BIDIR(a,b,c,d)\
CHECK_BIDIR(-(a),-(b),-(c),-(d))

        do{
            int i;
            int borderdist=0;
            end=1;

            CHECK_BIDIR2(0,0,0,1)
            CHECK_BIDIR2(0,0,1,0)
            CHECK_BIDIR2(0,1,0,0)
            CHECK_BIDIR2(1,0,0,0)

            for(i=8; i<limit; i++){
                int fx= motion_fx+vect[i][0];
                int fy= motion_fy+vect[i][1];
                int bx= motion_bx+vect[i][2];
                int by= motion_by+vect[i][3];
                if(borderdist<=0){
                    int a= (xmax - FFMAX(fx,bx))|(FFMIN(fx,bx) - xmin);
                    int b= (ymax - FFMAX(fy,by))|(FFMIN(fy,by) - ymin);
                    if((a|b) < 0)
                        map[(hashidx+hash[i])&255] = 1;
                }
                if(!map[(hashidx+hash[i])&255]){
                    int score;
                    map[(hashidx+hash[i])&255] = 1;
                    score= check_bidir_mv(s, fx, fy, bx, by, pred_fx, pred_fy, pred_bx, pred_by, 0, 16);
                    if(score < fbmin){
                        hashidx += hash[i];
                        fbmin= score;
                        motion_fx=fx;
                        motion_fy=fy;
                        motion_bx=bx;
                        motion_by=by;
                        end=0;
                        borderdist--;
                        if(borderdist<=0){
                            int a= FFMIN(xmax - FFMAX(fx,bx), FFMIN(fx,bx) - xmin);
                            int b= FFMIN(ymax - FFMAX(fy,by), FFMIN(fy,by) - ymin);
                            borderdist= FFMIN(a,b);
                        }
                    }
                }
            }
        }while(!end);
    }

    s->b_bidir_forw_mv_table[xy][0]= motion_fx;
    s->b_bidir_forw_mv_table[xy][1]= motion_fy;
    s->b_bidir_back_mv_table[xy][0]= motion_bx;
    s->b_bidir_back_mv_table[xy][1]= motion_by;

    return fbmin;
}