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
struct TYPE_5__ {size_t len; } ;
typedef  TYPE_1__ Heap ;

/* Variables and functions */
 scalar_t__ less (TYPE_1__*,size_t,size_t) ; 
 int /*<<< orphan*/  swap (TYPE_1__*,size_t,size_t) ; 

__attribute__((used)) static void
siftup(Heap *h, size_t k)
{
    for (;;) {
        size_t l = k*2 + 1; /* left child */
        size_t r = k*2 + 2; /* right child */

        /* find the smallest of the three */
        size_t s = k;
        if (l < h->len && less(h, l, s)) s = l;
        if (r < h->len && less(h, r, s)) s = r;

        if (s == k) {
            return; /* satisfies the heap property */
        }

        swap(h, k, s);
        k = s;
    }
}