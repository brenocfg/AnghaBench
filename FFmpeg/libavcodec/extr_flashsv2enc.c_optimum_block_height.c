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
struct TYPE_3__ {int diff_lines; int diff_blocks; int block_height; int comp_size; int tot_blocks; double rows; double cols; double image_height; } ;
typedef  TYPE_1__ FlashSV2Context ;

/* Variables and functions */
 int FFCLIP (int,int,int) ; 
 double block_size_fraction ; 
 int pow (int,double) ; 
 double sqrt (double) ; 

__attribute__((used)) static int optimum_block_height(FlashSV2Context * s)
{
#ifndef FLASHSV2_DUMB
    double save = (1-pow(s->diff_lines/s->diff_blocks/s->block_height, 0.5)) * s->comp_size/s->tot_blocks;
    double height = block_size_fraction * sqrt(0.5 * save * s->rows * s->cols) * s->image_height;
    int pheight = ((int) height);
    return FFCLIP(pheight & ~15, 256, 16);
#else
    return 64;
#endif
}