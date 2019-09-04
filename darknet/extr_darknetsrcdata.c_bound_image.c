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
struct TYPE_5__ {int w; int h; scalar_t__* data; } ;
typedef  TYPE_1__ image ;
struct TYPE_6__ {int member_0; int member_1; int member_2; int member_3; } ;
typedef  TYPE_2__ box ;

/* Variables and functions */

box bound_image(image im)
{
    int x,y;
    int minx = im.w;
    int miny = im.h;
    int maxx = 0;
    int maxy = 0;
    for(y = 0; y < im.h; ++y){
        for(x = 0; x < im.w; ++x){
            if(im.data[y*im.w + x]){
                minx = (x < minx) ? x : minx;
                miny = (y < miny) ? y : miny;
                maxx = (x > maxx) ? x : maxx;
                maxy = (y > maxy) ? y : maxy;
            }
        }
    }
    box b = {minx, miny, maxx-minx + 1, maxy-miny + 1};
    //printf("%f %f %f %f\n", b.x, b.y, b.w, b.h);
    return b;
}