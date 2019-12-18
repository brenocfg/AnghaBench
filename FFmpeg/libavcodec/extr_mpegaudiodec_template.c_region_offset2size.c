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
struct TYPE_3__ {int* region_size; int /*<<< orphan*/  big_values; } ;
typedef  TYPE_1__ GranuleDef ;

/* Variables and functions */
 int FFMIN (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void region_offset2size(GranuleDef *g)
{
    int i, k, j = 0;
    g->region_size[2] = 576 / 2;
    for (i = 0; i < 3; i++) {
        k = FFMIN(g->region_size[i], g->big_values);
        g->region_size[i] = k - j;
        j = k;
    }
}