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
struct TYPE_3__ {int w; int h; int c; float* data; } ;
typedef  TYPE_1__ image ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int) ; 

void transpose_image(image im)
{
    assert(im.w == im.h);
    int n, m;
    int c;
    for(c = 0; c < im.c; ++c){
        for(n = 0; n < im.w-1; ++n){
            for(m = n + 1; m < im.w; ++m){
                float swap = im.data[m + im.w*(n + im.h*c)];
                im.data[m + im.w*(n + im.h*c)] = im.data[n + im.w*(m + im.h*c)];
                im.data[n + im.w*(m + im.h*c)] = swap;
            }
        }
    }
}