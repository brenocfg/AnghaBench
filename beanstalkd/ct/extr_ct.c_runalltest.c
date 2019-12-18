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
struct TYPE_5__ {scalar_t__ f; } ;
typedef  TYPE_1__ Test ;

/* Variables and functions */
 int /*<<< orphan*/  start (TYPE_1__*) ; 
 int /*<<< orphan*/  waittest (TYPE_1__*) ; 

__attribute__((used)) static void
runalltest(Test *ts, int limit)
{
    int nrun = 0;
    Test *t;
    for (t=ts; t->f; t++) {
        if (nrun >= limit) {
            waittest(ts);
            nrun--;
        }
        start(t);
        nrun++;
    }
    for (; nrun; nrun--) {
        waittest(ts);
    }
}