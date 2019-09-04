#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int end; int capacity; int /*<<< orphan*/ * data; } ;
typedef  int /*<<< orphan*/  RingEntry ;
typedef  TYPE_1__ Ring ;

/* Variables and functions */
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 scalar_t__ ring_full (TYPE_1__*) ; 
 int /*<<< orphan*/  ring_grow (TYPE_1__*) ; 

void ring_put(Ring *ring, RingEntry *entry) {
    if (ring_full(ring)) {
        ring_grow(ring);
    }
    RingEntry *e = ring->data + ring->end;
    memcpy(e, entry, sizeof(RingEntry));
    ring->end = (ring->end + 1) % ring->capacity;
}