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
typedef  int int64_t ;
struct TYPE_8__ {int width; int height; TYPE_1__** band; } ;
struct TYPE_7__ {int spatial_decomposition_count; int* spatial_idwt_buffer; int /*<<< orphan*/  spatial_decomposition_type; int /*<<< orphan*/  temp_idwt_buffer; } ;
struct TYPE_6__ {int* ibuf; int width; int height; int stride; int qlog; } ;
typedef  TYPE_1__ SubBand ;
typedef  TYPE_2__ SnowContext ;
typedef  TYPE_3__ Plane ;
typedef  int IDWTELEM ;

/* Variables and functions */
 double QROOT ; 
 int /*<<< orphan*/  ff_spatial_idwt (int*,int /*<<< orphan*/ ,int,int,int,int /*<<< orphan*/ ,int) ; 
 double log2 (double) ; 
 int /*<<< orphan*/  memset (int*,int /*<<< orphan*/ ,int) ; 
 double sqrt (int) ; 

__attribute__((used)) static void calculate_visual_weight(SnowContext *s, Plane *p){
    int width = p->width;
    int height= p->height;
    int level, orientation, x, y;

    for(level=0; level<s->spatial_decomposition_count; level++){
        for(orientation=level ? 1 : 0; orientation<4; orientation++){
            SubBand *b= &p->band[level][orientation];
            IDWTELEM *ibuf= b->ibuf;
            int64_t error=0;

            memset(s->spatial_idwt_buffer, 0, sizeof(*s->spatial_idwt_buffer)*width*height);
            ibuf[b->width/2 + b->height/2*b->stride]= 256*16;
            ff_spatial_idwt(s->spatial_idwt_buffer, s->temp_idwt_buffer, width, height, width, s->spatial_decomposition_type, s->spatial_decomposition_count);
            for(y=0; y<height; y++){
                for(x=0; x<width; x++){
                    int64_t d= s->spatial_idwt_buffer[x + y*width]*16;
                    error += d*d;
                }
            }

            b->qlog= (int)(QROOT * log2(352256.0/sqrt(error)) + 0.5);
        }
    }
}