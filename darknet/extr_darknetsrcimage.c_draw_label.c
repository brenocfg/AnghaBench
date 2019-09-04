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
struct TYPE_6__ {int w; int h; int c; } ;
typedef  TYPE_1__ image ;

/* Variables and functions */
 float get_pixel (TYPE_1__,int,int,int) ; 
 int /*<<< orphan*/  set_pixel (TYPE_1__,int,int,int,float const) ; 

void draw_label(image a, int r, int c, image label, const float *rgb)
{
    int w = label.w;
    int h = label.h;
    if (r - h >= 0) r = r - h;

    int i, j, k;
    for(j = 0; j < h && j + r < a.h; ++j){
        for(i = 0; i < w && i + c < a.w; ++i){
            for(k = 0; k < label.c; ++k){
                float val = get_pixel(label, i, j, k);
                set_pixel(a, i+c, j+r, k, rgb[k] * val);
            }
        }
    }
}