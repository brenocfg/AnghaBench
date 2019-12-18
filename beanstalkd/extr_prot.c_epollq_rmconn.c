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
struct TYPE_4__ {struct TYPE_4__* next; } ;
typedef  TYPE_1__ Conn ;

/* Variables and functions */
 TYPE_1__* epollq ; 

__attribute__((used)) static void
epollq_rmconn(Conn *c)
{
    Conn *x, *newhead = NULL;

    while (epollq) {
        // x as next element from epollq.
        x = epollq;
        epollq = epollq->next;
        x->next = NULL;

        // put x back into newhead list.
        if (x != c) {
            x->next = newhead;
            newhead = x;
        }
    }
    epollq = newhead;
}