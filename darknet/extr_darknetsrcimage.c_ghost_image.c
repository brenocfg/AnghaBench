#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int w; int c; int h; } ;
typedef  TYPE_1__ image ;

/* Variables and functions */
 float get_pixel (TYPE_1__,int,int,int) ; 
 int /*<<< orphan*/  set_pixel (TYPE_1__,int,int,int,float) ; 
 float sqrt (int) ; 

void ghost_image(image source, image dest, int dx, int dy)
{
    int x,y,k;
    float max_dist = sqrt((-source.w/2. + .5)*(-source.w/2. + .5));
    for(k = 0; k < source.c; ++k){
        for(y = 0; y < source.h; ++y){
            for(x = 0; x < source.w; ++x){
                float dist = sqrt((x - source.w/2. + .5)*(x - source.w/2. + .5) + (y - source.h/2. + .5)*(y - source.h/2. + .5));
                float alpha = (1 - dist/max_dist);
                if(alpha < 0) alpha = 0;
                float v1 = get_pixel(source, x,y,k);
                float v2 = get_pixel(dest, dx+x,dy+y,k);
                float val = alpha*v1 + (1-alpha)*v2;
                set_pixel(dest, dx+x, dy+y, k, val);
            }
        }
    }
}