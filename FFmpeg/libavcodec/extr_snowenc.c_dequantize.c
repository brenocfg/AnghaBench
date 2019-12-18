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
struct TYPE_6__ {int const qbias; int /*<<< orphan*/  qlog; } ;
struct TYPE_5__ {int width; int height; int /*<<< orphan*/  qlog; } ;
typedef  TYPE_1__ SubBand ;
typedef  TYPE_2__ SnowContext ;
typedef  int IDWTELEM ;

/* Variables and functions */
 int /*<<< orphan*/  LOSSLESS_QLOG ; 
 int const QBIAS_SHIFT ; 
 int QEXPSHIFT ; 
 int QROOT ; 
 int const QSHIFT ; 
 int av_clip (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int const* ff_qexp ; 

__attribute__((used)) static void dequantize(SnowContext *s, SubBand *b, IDWTELEM *src, int stride){
    const int w= b->width;
    const int h= b->height;
    const int qlog= av_clip(s->qlog + b->qlog, 0, QROOT*16);
    const int qmul= ff_qexp[qlog&(QROOT-1)]<<(qlog>>QSHIFT);
    const int qadd= (s->qbias*qmul)>>QBIAS_SHIFT;
    int x,y;

    if(s->qlog == LOSSLESS_QLOG) return;

    for(y=0; y<h; y++){
        for(x=0; x<w; x++){
            int i= src[x + y*stride];
            if(i<0){
                src[x + y*stride]= -((-i*qmul + qadd)>>(QEXPSHIFT)); //FIXME try different bias
            }else if(i>0){
                src[x + y*stride]=  (( i*qmul + qadd)>>(QEXPSHIFT));
            }
        }
    }
}