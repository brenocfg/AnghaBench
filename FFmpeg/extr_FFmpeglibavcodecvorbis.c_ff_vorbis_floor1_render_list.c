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
struct TYPE_3__ {int sort; int x; } ;
typedef  TYPE_1__ vorbis_floor1_entry ;
typedef  int uint16_t ;

/* Variables and functions */
 int FFMIN (int,int) ; 
 int /*<<< orphan*/  render_line (int,int,int,int,float*) ; 

void ff_vorbis_floor1_render_list(vorbis_floor1_entry * list, int values,
                                  uint16_t *y_list, int *flag,
                                  int multiplier, float *out, int samples)
{
    int lx, ly, i;
    lx = 0;
    ly = y_list[0] * multiplier;
    for (i = 1; i < values; i++) {
        int pos = list[i].sort;
        if (flag[pos]) {
            int x1 = list[pos].x;
            int y1 = y_list[pos] * multiplier;
            if (lx < samples)
                render_line(lx, ly, FFMIN(x1,samples), y1, out);
            lx = x1;
            ly = y1;
        }
        if (lx >= samples)
            break;
    }
    if (lx < samples)
        render_line(lx, ly, samples, ly, out);
}