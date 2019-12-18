#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ int64 ;
struct TYPE_4__ {scalar_t__ deadline_at; } ;
struct TYPE_5__ {TYPE_1__ r; } ;
typedef  TYPE_2__ Job ;
typedef  int /*<<< orphan*/  Conn ;

/* Variables and functions */
 scalar_t__ SAFETY_MARGIN ; 
 TYPE_2__* connsoonestjob (int /*<<< orphan*/ *) ; 
 scalar_t__ nanoseconds () ; 

int
conndeadlinesoon(Conn *c)
{
    int64 t = nanoseconds();
    Job *j = connsoonestjob(c);

    return j && t >= j->r.deadline_at - SAFETY_MARGIN;
}