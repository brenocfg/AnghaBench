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
struct TYPE_6__ {int block_type; int* region_size; } ;
struct TYPE_5__ {int sample_rate_index; } ;
typedef  TYPE_1__ MPADecodeContext ;
typedef  TYPE_2__ GranuleDef ;

/* Variables and functions */

__attribute__((used)) static void init_short_region(MPADecodeContext *s, GranuleDef *g)
{
    if (g->block_type == 2) {
        if (s->sample_rate_index != 8)
            g->region_size[0] = (36 / 2);
        else
            g->region_size[0] = (72 / 2);
    } else {
        if (s->sample_rate_index <= 2)
            g->region_size[0] = (36 / 2);
        else if (s->sample_rate_index != 8)
            g->region_size[0] = (54 / 2);
        else
            g->region_size[0] = (108 / 2);
    }
    g->region_size[1] = (576 / 2);
}