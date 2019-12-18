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
struct TYPE_3__ {int c_superblock_width; int y_superblock_width; int c_superblock_height; int y_superblock_height; int* fragment_width; int* fragment_height; int* superblock_fragments; int* fragment_start; } ;
typedef  TYPE_1__ Vp3DecodeContext ;

/* Variables and functions */
 int** hilbert_offset ; 

__attribute__((used)) static int init_block_mapping(Vp3DecodeContext *s)
{
    int sb_x, sb_y, plane;
    int x, y, i, j = 0;

    for (plane = 0; plane < 3; plane++) {
        int sb_width    = plane ? s->c_superblock_width
                                : s->y_superblock_width;
        int sb_height   = plane ? s->c_superblock_height
                                : s->y_superblock_height;
        int frag_width  = s->fragment_width[!!plane];
        int frag_height = s->fragment_height[!!plane];

        for (sb_y = 0; sb_y < sb_height; sb_y++)
            for (sb_x = 0; sb_x < sb_width; sb_x++)
                for (i = 0; i < 16; i++) {
                    x = 4 * sb_x + hilbert_offset[i][0];
                    y = 4 * sb_y + hilbert_offset[i][1];

                    if (x < frag_width && y < frag_height)
                        s->superblock_fragments[j++] = s->fragment_start[plane] +
                                                       y * frag_width + x;
                    else
                        s->superblock_fragments[j++] = -1;
                }
    }

    return 0;  /* successful path out */
}