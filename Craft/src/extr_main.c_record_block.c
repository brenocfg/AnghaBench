#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int x; int y; int z; int w; } ;
struct TYPE_4__ {TYPE_1__ block0; int /*<<< orphan*/  block1; } ;
typedef  int /*<<< orphan*/  Block ;

/* Variables and functions */
 TYPE_2__* g ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,TYPE_1__*,int) ; 

void record_block(int x, int y, int z, int w) {
    memcpy(&g->block1, &g->block0, sizeof(Block));
    g->block0.x = x;
    g->block0.y = y;
    g->block0.z = z;
    g->block0.w = w;
}