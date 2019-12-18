#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_17__   TYPE_7__ ;
typedef  struct TYPE_16__   TYPE_6__ ;
typedef  struct TYPE_15__   TYPE_5__ ;
typedef  struct TYPE_14__   TYPE_4__ ;
typedef  struct TYPE_13__   TYPE_3__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
struct TYPE_15__ {int x; int coeff; } ;
typedef  TYPE_5__ x_and_coeff ;
typedef  int uint16_t ;
struct TYPE_17__ {int /*<<< orphan*/  avctx; int /*<<< orphan*/  c; } ;
struct TYPE_16__ {int width; int height; int /*<<< orphan*/ ** state; TYPE_5__* x_coeff; } ;
struct TYPE_14__ {int coeff; } ;
struct TYPE_13__ {int x; } ;
struct TYPE_12__ {int x; } ;
struct TYPE_11__ {int coeff; } ;
typedef  TYPE_6__ SubBand ;
typedef  TYPE_7__ SnowContext ;

/* Variables and functions */
 int /*<<< orphan*/  AV_LOG_ERROR ; 
 int FFMIN (int,int const) ; 
 int INT_MAX ; 
 int /*<<< orphan*/  av_assert2 (int) ; 
 int /*<<< orphan*/  av_log (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int av_log2 (int) ; 
 int* ff_quant3bA ; 
 int get_rac (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int get_symbol2 (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static inline void unpack_coeffs(SnowContext *s, SubBand *b, SubBand * parent, int orientation){
    const int w= b->width;
    const int h= b->height;
    int x,y;

    int run, runs;
    x_and_coeff *xc= b->x_coeff;
    x_and_coeff *prev_xc= NULL;
    x_and_coeff *prev2_xc= xc;
    x_and_coeff *parent_xc= parent ? parent->x_coeff : NULL;
    x_and_coeff *prev_parent_xc= parent_xc;

    runs= get_symbol2(&s->c, b->state[30], 0);
    if(runs-- > 0) run= get_symbol2(&s->c, b->state[1], 3);
    else           run= INT_MAX;

    for(y=0; y<h; y++){
        int v=0;
        int lt=0, t=0, rt=0;

        if(y && prev_xc->x == 0){
            rt= prev_xc->coeff;
        }
        for(x=0; x<w; x++){
            int p=0;
            const int l= v;

            lt= t; t= rt;

            if(y){
                if(prev_xc->x <= x)
                    prev_xc++;
                if(prev_xc->x == x + 1)
                    rt= prev_xc->coeff;
                else
                    rt=0;
            }
            if(parent_xc){
                if(x>>1 > parent_xc->x){
                    parent_xc++;
                }
                if(x>>1 == parent_xc->x){
                    p= parent_xc->coeff;
                }
            }
            if(/*ll|*/l|lt|t|rt|p){
                int context= av_log2(/*FFABS(ll) + */3*(l>>1) + (lt>>1) + (t&~1) + (rt>>1) + (p>>1));

                v=get_rac(&s->c, &b->state[0][context]);
                if(v){
                    v= 2*(get_symbol2(&s->c, b->state[context + 2], context-4) + 1);
                    v+=get_rac(&s->c, &b->state[0][16 + 1 + 3 + ff_quant3bA[l&0xFF] + 3*ff_quant3bA[t&0xFF]]);
                    if ((uint16_t)v != v) {
                        av_log(s->avctx, AV_LOG_ERROR, "Coefficient damaged\n");
                        v = 1;
                    }
                    xc->x=x;
                    (xc++)->coeff= v;
                }
            }else{
                if(!run){
                    if(runs-- > 0) run= get_symbol2(&s->c, b->state[1], 3);
                    else           run= INT_MAX;
                    v= 2*(get_symbol2(&s->c, b->state[0 + 2], 0-4) + 1);
                    v+=get_rac(&s->c, &b->state[0][16 + 1 + 3]);
                    if ((uint16_t)v != v) {
                        av_log(s->avctx, AV_LOG_ERROR, "Coefficient damaged\n");
                        v = 1;
                    }

                    xc->x=x;
                    (xc++)->coeff= v;
                }else{
                    int max_run;
                    run--;
                    v=0;
                    av_assert2(run >= 0);
                    if(y) max_run= FFMIN(run, prev_xc->x - x - 2);
                    else  max_run= FFMIN(run, w-x-1);
                    if(parent_xc)
                        max_run= FFMIN(max_run, 2*parent_xc->x - x - 1);
                    av_assert2(max_run >= 0 && max_run <= run);

                    x+= max_run;
                    run-= max_run;
                }
            }
        }
        (xc++)->x= w+1; //end marker
        prev_xc= prev2_xc;
        prev2_xc= xc;

        if(parent_xc){
            if(y&1){
                while(parent_xc->x != parent->width+1)
                    parent_xc++;
                parent_xc++;
                prev_parent_xc= parent_xc;
            }else{
                parent_xc= prev_parent_xc;
            }
        }
    }

    (xc++)->x= w+1; //end marker
}