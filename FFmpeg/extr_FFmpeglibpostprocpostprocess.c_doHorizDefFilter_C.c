#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int uint8_t ;
struct TYPE_3__ {int QP; } ;
typedef  TYPE_1__ PPContext ;

/* Variables and functions */
 int BLOCK_SIZE ; 
 int const FFABS (int const) ; 
 int FFMAX (int,int const) ; 
 int FFMIN (int,int const) ; 
 int FFSIGN (int const) ; 

__attribute__((used)) static inline void doHorizDefFilter_C(uint8_t dst[], int stride, const PPContext *c)
{
    int y;
    for(y=0; y<BLOCK_SIZE; y++){
        const int middleEnergy= 5*(dst[4] - dst[3]) + 2*(dst[2] - dst[5]);

        if(FFABS(middleEnergy) < 8*c->QP){
            const int q=(dst[3] - dst[4])/2;
            const int leftEnergy=  5*(dst[2] - dst[1]) + 2*(dst[0] - dst[3]);
            const int rightEnergy= 5*(dst[6] - dst[5]) + 2*(dst[4] - dst[7]);

            int d= FFABS(middleEnergy) - FFMIN( FFABS(leftEnergy), FFABS(rightEnergy) );
            d= FFMAX(d, 0);

            d= (5*d + 32) >> 6;
            d*= FFSIGN(-middleEnergy);

            if(q>0)
            {
                d = FFMAX(d, 0);
                d = FFMIN(d, q);
            }
            else
            {
                d = FFMIN(d, 0);
                d = FFMAX(d, q);
            }

            dst[3]-= d;
            dst[4]+= d;
        }
        dst+= stride;
    }
}