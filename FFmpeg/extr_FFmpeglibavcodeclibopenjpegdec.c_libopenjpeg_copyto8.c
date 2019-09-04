#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int uint8_t ;
struct TYPE_7__ {int numcomps; TYPE_1__* comps; } ;
typedef  TYPE_2__ opj_image_t ;
struct TYPE_8__ {int** data; int* linesize; } ;
struct TYPE_6__ {int* data; int h; int w; int sgnd; } ;
typedef  TYPE_3__ AVFrame ;

/* Variables and functions */

__attribute__((used)) static inline void libopenjpeg_copyto8(AVFrame *picture, opj_image_t *image) {
    int *comp_data;
    uint8_t *img_ptr;
    int index, x, y;

    for (index = 0; index < image->numcomps; index++) {
        comp_data = image->comps[index].data;
        for (y = 0; y < image->comps[index].h; y++) {
            img_ptr = picture->data[index] + y * picture->linesize[index];
            for (x = 0; x < image->comps[index].w; x++) {
                *img_ptr = 0x80 * image->comps[index].sgnd + *comp_data;
                img_ptr++;
                comp_data++;
            }
        }
    }
}