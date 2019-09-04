#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int uint64_t ;
typedef  int uint32_t ;
struct range_box {int len; int start; } ;
struct color_ref {int color; int count; } ;

/* Variables and functions */

__attribute__((used)) static uint32_t get_avg_color(struct color_ref * const *refs,
                              const struct range_box *box)
{
    int i;
    const int n = box->len;
    uint64_t r = 0, g = 0, b = 0, div = 0;

    for (i = 0; i < n; i++) {
        const struct color_ref *ref = refs[box->start + i];
        r += (ref->color >> 16 & 0xff) * ref->count;
        g += (ref->color >>  8 & 0xff) * ref->count;
        b += (ref->color       & 0xff) * ref->count;
        div += ref->count;
    }

    r = r / div;
    g = g / div;
    b = b / div;

    return 0xffU<<24 | r<<16 | g<<8 | b;
}