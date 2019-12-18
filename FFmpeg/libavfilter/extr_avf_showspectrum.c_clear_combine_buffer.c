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
struct TYPE_3__ {double* combine_buffer; } ;
typedef  TYPE_1__ ShowSpectrumContext ;

/* Variables and functions */

__attribute__((used)) static void clear_combine_buffer(ShowSpectrumContext *s, int size)
{
    int y;

    for (y = 0; y < size; y++) {
        s->combine_buffer[3 * y    ] = 0;
        s->combine_buffer[3 * y + 1] = 127.5;
        s->combine_buffer[3 * y + 2] = 127.5;
    }
}