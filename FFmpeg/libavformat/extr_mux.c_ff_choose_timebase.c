#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int den; int num; } ;
struct TYPE_5__ {TYPE_2__ time_base; } ;
typedef  TYPE_1__ AVStream ;
typedef  TYPE_2__ AVRational ;
typedef  int /*<<< orphan*/  AVFormatContext ;

/* Variables and functions */

AVRational ff_choose_timebase(AVFormatContext *s, AVStream *st, int min_precision)
{
    AVRational q;
    int j;

    q = st->time_base;

    for (j=2; j<14; j+= 1+(j>2))
        while (q.den / q.num < min_precision && q.num % j == 0)
            q.num /= j;
    while (q.den / q.num < min_precision && q.den < (1<<24))
        q.den <<= 1;

    return q;
}