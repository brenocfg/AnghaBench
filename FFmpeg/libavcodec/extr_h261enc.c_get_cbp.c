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
typedef  int /*<<< orphan*/  int16_t ;
struct TYPE_3__ {scalar_t__* block_last_index; } ;
typedef  TYPE_1__ MpegEncContext ;

/* Variables and functions */

__attribute__((used)) static inline int get_cbp(MpegEncContext *s, int16_t block[6][64])
{
    int i, cbp;
    cbp = 0;
    for (i = 0; i < 6; i++)
        if (s->block_last_index[i] >= 0)
            cbp |= 1 << (5 - i);
    return cbp;
}