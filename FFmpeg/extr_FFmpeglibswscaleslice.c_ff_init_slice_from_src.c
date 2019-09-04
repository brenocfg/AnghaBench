#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
struct TYPE_5__ {int width; TYPE_1__* plane; } ;
struct TYPE_4__ {int sliceY; int available_lines; int sliceH; int /*<<< orphan*/ ** line; } ;
typedef  TYPE_2__ SwsSlice ;

/* Variables and functions */
 int FFMAX (int,int) ; 

int ff_init_slice_from_src(SwsSlice * s, uint8_t *src[4], int stride[4], int srcW, int lumY, int lumH, int chrY, int chrH, int relative)
{
    int i = 0;

    const int start[4] = {lumY,
                          chrY,
                          chrY,
                          lumY};

    const int end[4] = {lumY +lumH,
                        chrY + chrH,
                        chrY + chrH,
                        lumY + lumH};

    uint8_t *const src_[4] = {src[0] + (relative ? 0 : start[0]) * stride[0],
                              src[1] + (relative ? 0 : start[1]) * stride[1],
                              src[2] + (relative ? 0 : start[2]) * stride[2],
                              src[3] + (relative ? 0 : start[3]) * stride[3]};

    s->width = srcW;

    for (i = 0; i < 4; ++i) {
        int j;
        int first = s->plane[i].sliceY;
        int n = s->plane[i].available_lines;
        int lines = end[i] - start[i];
        int tot_lines = end[i] - first;

        if (start[i] >= first && n >= tot_lines) {
            s->plane[i].sliceH = FFMAX(tot_lines, s->plane[i].sliceH);
            for (j = 0; j < lines; j+= 1)
                s->plane[i].line[start[i] - first + j] = src_[i] +  j * stride[i];
        } else {
            s->plane[i].sliceY = start[i];
            lines = lines > n ? n : lines;
            s->plane[i].sliceH = lines;
            for (j = 0; j < lines; j+= 1)
                s->plane[i].line[j] = src_[i] +  j * stride[i];
        }

    }

    return 0;
}