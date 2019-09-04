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
typedef  size_t uint8_t ;
struct TYPE_3__ {size_t** data; int* linesize; } ;
typedef  TYPE_1__ AVFrame ;

/* Variables and functions */
 size_t* ulti_chromas ; 
 size_t* ulti_lumas ; 

__attribute__((used)) static void ulti_convert_yuv(AVFrame *frame, int x, int y,
                             uint8_t *luma,int chroma)
{
    uint8_t *y_plane, *cr_plane, *cb_plane;
    int i;

    y_plane = frame->data[0] + x + y * frame->linesize[0];
    cr_plane = frame->data[1] + (x / 4) + (y / 4) * frame->linesize[1];
    cb_plane = frame->data[2] + (x / 4) + (y / 4) * frame->linesize[2];

    cr_plane[0] = ulti_chromas[chroma >> 4];

    cb_plane[0] = ulti_chromas[chroma & 0xF];


    for(i = 0; i < 16; i++){
        y_plane[i & 3] = ulti_lumas[luma[i]];
        if((i & 3) == 3) { //next row
            y_plane += frame->linesize[0];
        }
    }
}