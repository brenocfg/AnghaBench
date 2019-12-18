#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int /*<<< orphan*/  index; int /*<<< orphan*/  start_ts; } ;
typedef  TYPE_1__ Interval ;

/* Variables and functions */
 int FFDIFFSIGN (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int cmp_intervals(const void *a, const void *b)
{
    const Interval *i1 = a;
    const Interval *i2 = b;
    return 2 * FFDIFFSIGN(i1->start_ts, i2->start_ts) + FFDIFFSIGN(i1->index, i2->index);
}