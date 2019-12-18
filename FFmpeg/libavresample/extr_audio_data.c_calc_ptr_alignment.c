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
struct TYPE_3__ {int planes; int ptr_align; scalar_t__* data; } ;
typedef  TYPE_1__ AudioData ;

/* Variables and functions */

__attribute__((used)) static void calc_ptr_alignment(AudioData *a)
{
    int p;
    int min_align = 128;

    for (p = 0; p < a->planes; p++) {
        int cur_align = 128;
        while ((intptr_t)a->data[p] % cur_align)
            cur_align >>= 1;
        if (cur_align < min_align)
            min_align = cur_align;
    }
    a->ptr_align = min_align;
}