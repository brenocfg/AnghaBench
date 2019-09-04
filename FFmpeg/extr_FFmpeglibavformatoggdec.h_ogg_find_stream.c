#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct ogg {int nstreams; TYPE_1__* streams; } ;
struct TYPE_2__ {int serial; } ;

/* Variables and functions */

__attribute__((used)) static inline int
ogg_find_stream (struct ogg * ogg, int serial)
{
    int i;

    for (i = 0; i < ogg->nstreams; i++)
        if (ogg->streams[i].serial == serial)
            return i;

    return -1;
}