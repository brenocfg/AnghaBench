#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {int resv; TYPE_2__* tail; TYPE_1__* cur; int /*<<< orphan*/  use; } ;
typedef  TYPE_3__ Wal ;
struct TYPE_8__ {int free; int resv; } ;
struct TYPE_7__ {int free; int resv; } ;

/* Variables and functions */
 int /*<<< orphan*/  balance (TYPE_3__*,int) ; 
 int needfree (TYPE_3__*,int) ; 
 int /*<<< orphan*/  twarnx (char*) ; 

__attribute__((used)) static int
reserve(Wal *w, int n)
{
    int r;

    // return value must be nonzero but is otherwise ignored
    if (!w->use) return 1;

    if (w->cur->free >= n) {
        w->cur->free -= n;
        w->cur->resv += n;
        w->resv += n;
        return n;
    }

    r = needfree(w, n);
    if (r != n) {
        twarnx("needfree");
        return 0;
    }

    w->tail->free -= n;
    w->tail->resv += n;
    w->resv += n;
    if (!balance(w, n)) {
        // error; undo the reservation
        w->resv -= n;
        w->tail->resv -= n;
        w->tail->free += n;
        return 0;
    }

    return n;
}