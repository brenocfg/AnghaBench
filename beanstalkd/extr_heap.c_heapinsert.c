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
struct TYPE_5__ {size_t len; size_t cap; void** data; } ;
typedef  TYPE_1__ Heap ;

/* Variables and functions */
 int /*<<< orphan*/  free (void**) ; 
 void** malloc (int) ; 
 int /*<<< orphan*/  memcpy (void**,void**,int) ; 
 int /*<<< orphan*/  set (TYPE_1__*,size_t,void*) ; 
 int /*<<< orphan*/  siftdown (TYPE_1__*,size_t) ; 

int
heapinsert(Heap *h, void *x)
{
    if (h->len == h->cap) {
        void **ndata;
        size_t ncap = (h->len+1) * 2; /* allocate twice what we need */

        ndata = malloc(sizeof(void*) * ncap);
        if (!ndata) {
            return 0;
        }

        memcpy(ndata, h->data, sizeof(void*) * h->len);
        free(h->data);
        h->data = ndata;
        h->cap = ncap;
    }

    size_t k = h->len;
    h->len++;
    set(h, k, x);
    siftdown(h, k);
    return 1;
}