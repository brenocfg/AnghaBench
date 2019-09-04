#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_3__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int geotag_count; TYPE_3__* geotags; } ;
typedef  TYPE_1__ TiffContext ;
struct TYPE_5__ {struct TYPE_5__* val; } ;

/* Variables and functions */
 int /*<<< orphan*/  av_freep (TYPE_3__**) ; 

__attribute__((used)) static void free_geotags(TiffContext *const s)
{
    int i;
    for (i = 0; i < s->geotag_count; i++) {
        if (s->geotags[i].val)
            av_freep(&s->geotags[i].val);
    }
    av_freep(&s->geotags);
    s->geotag_count = 0;
}