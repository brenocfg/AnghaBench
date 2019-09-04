#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int w; int h; int* data; } ;
typedef  TYPE_1__ image ;

/* Variables and functions */

void or_image(image src, image dest, int c)
{
    int i;
    for(i = 0; i < src.w*src.h; ++i){
        if(src.data[i]) dest.data[dest.w*dest.h*c + i] = 1;
    }
}