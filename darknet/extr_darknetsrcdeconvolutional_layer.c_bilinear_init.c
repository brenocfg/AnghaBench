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
struct TYPE_3__ {int size; int n; int c; float* weights; } ;
typedef  TYPE_1__ layer ;

/* Variables and functions */
 int fabs (int) ; 

void bilinear_init(layer l)
{
    int i,j,f;
    float center = (l.size-1) / 2.;
    for(f = 0; f < l.n; ++f){
        for(j = 0; j < l.size; ++j){
            for(i = 0; i < l.size; ++i){
                float val = (1 - fabs(i - center)) * (1 - fabs(j - center));
                int c = f%l.c;
                int ind = f*l.size*l.size*l.c + c*l.size*l.size + j*l.size + i;
                l.weights[ind] = val;
            }
        }
    }
}