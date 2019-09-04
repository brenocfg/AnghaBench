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
struct TYPE_3__ {int version; int* mv; } ;
typedef  TYPE_1__ FourXContext ;

/* Variables and functions */
 int** mv ; 

__attribute__((used)) static void init_mv(FourXContext *f, int linesize)
{
    int i;

    for (i = 0; i < 256; i++) {
        if (f->version > 1)
            f->mv[i] = mv[i][0] + mv[i][1] * linesize / 2;
        else
            f->mv[i] = (i & 15) - 8 + ((i >> 4) - 8) * linesize / 2;
    }
}