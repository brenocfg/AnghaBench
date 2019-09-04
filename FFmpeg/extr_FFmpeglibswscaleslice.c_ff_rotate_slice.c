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
struct TYPE_5__ {TYPE_1__* plane; } ;
struct TYPE_4__ {int available_lines; int sliceY; int sliceH; } ;
typedef  TYPE_2__ SwsSlice ;

/* Variables and functions */

int ff_rotate_slice(SwsSlice *s, int lum, int chr)
{
    int i;
    if (lum) {
        for (i = 0; i < 4; i+=3) {
            int n = s->plane[i].available_lines;
            int l = lum - s->plane[i].sliceY;

            if (l >= n * 2) {
                s->plane[i].sliceY += n;
                s->plane[i].sliceH -= n;
            }
        }
    }
    if (chr) {
        for (i = 1; i < 3; ++i) {
            int n = s->plane[i].available_lines;
            int l = chr - s->plane[i].sliceY;

            if (l >= n * 2) {
                s->plane[i].sliceY += n;
                s->plane[i].sliceH -= n;
            }
        }
    }
    return 0;
}