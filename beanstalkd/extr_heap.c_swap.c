#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {void** data; } ;
typedef  TYPE_1__ Heap ;

/* Variables and functions */
 int /*<<< orphan*/  set (TYPE_1__*,size_t,void*) ; 

__attribute__((used)) static void
swap(Heap *h, size_t a, size_t b)
{
    void *tmp;

    tmp = h->data[a];
    set(h, a, h->data[b]);
    set(h, b, tmp);
}