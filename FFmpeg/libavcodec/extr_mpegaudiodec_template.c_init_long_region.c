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
struct TYPE_6__ {int* region_size; } ;
struct TYPE_5__ {size_t sample_rate_index; } ;
typedef  TYPE_1__ MPADecodeContext ;
typedef  TYPE_2__ GranuleDef ;

/* Variables and functions */
 int FFMIN (int,int) ; 
 int** band_index_long ; 

__attribute__((used)) static void init_long_region(MPADecodeContext *s, GranuleDef *g,
                             int ra1, int ra2)
{
    int l;
    g->region_size[0] = band_index_long[s->sample_rate_index][ra1 + 1] >> 1;
    /* should not overflow */
    l = FFMIN(ra1 + ra2 + 2, 22);
    g->region_size[1] = band_index_long[s->sample_rate_index][      l] >> 1;
}