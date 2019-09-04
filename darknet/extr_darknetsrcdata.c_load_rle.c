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
struct TYPE_3__ {int* data; int h; int w; int c; } ;
typedef  TYPE_1__ image ;

/* Variables and functions */

void load_rle(image im, int *rle, int n)
{
    int count = 0;
    int curr = 0;
    int i,j;
    for(i = 0; i < n; ++i){
        for(j = 0; j < rle[i]; ++j){
            im.data[count++] = curr;
        }
        curr = 1 - curr;
    }
    for(; count < im.h*im.w*im.c; ++count){
        im.data[count] = curr;
    }
}