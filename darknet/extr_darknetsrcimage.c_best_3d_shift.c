#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int w; int h; int c; int /*<<< orphan*/  data; } ;
typedef  TYPE_1__ image ;

/* Variables and functions */
 float FLT_MAX ; 
 TYPE_1__ crop_image (TYPE_1__,int /*<<< orphan*/ ,int,int,int) ; 
 float dist_array (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  free_image (TYPE_1__) ; 
 int /*<<< orphan*/  printf (char*,int,float) ; 

int best_3d_shift(image a, image b, int min, int max)
{
    int i;
    int best = 0;
    float best_distance = FLT_MAX;
    for(i = min; i <= max; i += 2){
        image c = crop_image(b, 0, i, b.w, b.h);
        float d = dist_array(c.data, a.data, a.w*a.h*a.c, 100);
        if(d < best_distance){
            best_distance = d;
            best = i;
        }
        printf("%d %f\n", i, d);
        free_image(c);
    }
    return best;
}