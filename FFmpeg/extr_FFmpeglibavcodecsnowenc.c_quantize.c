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
struct TYPE_6__ {int /*<<< orphan*/  qlog; } ;
struct TYPE_5__ {int width; int height; int /*<<< orphan*/  qlog; } ;
typedef  TYPE_1__ SubBand ;
typedef  TYPE_2__ SnowContext ;
typedef  int IDWTELEM ;
typedef  void* DWTELEM ;

/* Variables and functions */
 int const ENCODER_EXTRA_BITS ; 
 int /*<<< orphan*/  LOSSLESS_QLOG ; 
 int const QEXPSHIFT ; 
 int QROOT ; 
 int const QSHIFT ; 
 int av_clip (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int const* ff_qexp ; 

__attribute__((used)) static void quantize(SnowContext *s, SubBand *b, IDWTELEM *dst, DWTELEM *src, int stride, int bias){
    const int w= b->width;
    const int h= b->height;
    const int qlog= av_clip(s->qlog + b->qlog, 0, QROOT*16);
    const int qmul= ff_qexp[qlog&(QROOT-1)]<<((qlog>>QSHIFT) + ENCODER_EXTRA_BITS);
    int x,y, thres1, thres2;

    if(s->qlog == LOSSLESS_QLOG){
        for(y=0; y<h; y++)
            for(x=0; x<w; x++)
                dst[x + y*stride]= src[x + y*stride];
        return;
    }

    bias= bias ? 0 : (3*qmul)>>3;
    thres1= ((qmul - bias)>>QEXPSHIFT) - 1;
    thres2= 2*thres1;

    if(!bias){
        for(y=0; y<h; y++){
            for(x=0; x<w; x++){
                int i= src[x + y*stride];

                if((unsigned)(i+thres1) > thres2){
                    if(i>=0){
                        i<<= QEXPSHIFT;
                        i/= qmul; //FIXME optimize
                        dst[x + y*stride]=  i;
                    }else{
                        i= -i;
                        i<<= QEXPSHIFT;
                        i/= qmul; //FIXME optimize
                        dst[x + y*stride]= -i;
                    }
                }else
                    dst[x + y*stride]= 0;
            }
        }
    }else{
        for(y=0; y<h; y++){
            for(x=0; x<w; x++){
                int i= src[x + y*stride];

                if((unsigned)(i+thres1) > thres2){
                    if(i>=0){
                        i<<= QEXPSHIFT;
                        i= (i + bias) / qmul; //FIXME optimize
                        dst[x + y*stride]=  i;
                    }else{
                        i= -i;
                        i<<= QEXPSHIFT;
                        i= (i + bias) / qmul; //FIXME optimize
                        dst[x + y*stride]= -i;
                    }
                }else
                    dst[x + y*stride]= 0;
            }
        }
    }
}