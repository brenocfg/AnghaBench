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
struct TYPE_3__ {int p; int q; int x; int y; int z; int w; int /*<<< orphan*/  type; } ;
typedef  TYPE_1__ RingEntry ;
typedef  int /*<<< orphan*/  Ring ;

/* Variables and functions */
 int /*<<< orphan*/  BLOCK ; 
 int /*<<< orphan*/  ring_put (int /*<<< orphan*/ *,TYPE_1__*) ; 

void ring_put_block(Ring *ring, int p, int q, int x, int y, int z, int w) {
    RingEntry entry;
    entry.type = BLOCK;
    entry.p = p;
    entry.q = q;
    entry.x = x;
    entry.y = y;
    entry.z = z;
    entry.w = w;
    ring_put(ring, &entry);
}