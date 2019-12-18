#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {TYPE_4__* cur; int /*<<< orphan*/  tail; } ;
typedef  TYPE_1__ Wal ;
struct TYPE_9__ {int resv; } ;

/* Variables and functions */
 int balancerest (TYPE_1__*,TYPE_4__*,int) ; 
 int /*<<< orphan*/  moveresv (int /*<<< orphan*/ ,TYPE_4__*,int) ; 
 int needfree (TYPE_1__*,int) ; 
 int /*<<< orphan*/  twarnx (char*) ; 
 int /*<<< orphan*/  usenext (TYPE_1__*) ; 

__attribute__((used)) static int
balance(Wal *w, int n)
{
    // Invariant 1
    // (this loop will run at most once)
    while (w->cur->resv < n) {
        int m = w->cur->resv;

        int r = needfree(w, m);
        if (r != m) {
            twarnx("needfree");
            return 0;
        }

        moveresv(w->tail, w->cur, m);
        usenext(w);
    }

    // Invariants 2 and 3
    return balancerest(w, w->cur, n);
}