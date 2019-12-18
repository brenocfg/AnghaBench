#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int int64 ;
struct TYPE_8__ {int deadline_at; } ;
struct TYPE_10__ {TYPE_1__ r; } ;
struct TYPE_9__ {scalar_t__ pending_timeout; } ;
typedef  TYPE_2__ Conn ;

/* Variables and functions */
 int INT64_MAX ; 
 int SAFETY_MARGIN ; 
 scalar_t__ conn_waiting (TYPE_2__*) ; 
 TYPE_5__* connsoonestjob (TYPE_2__*) ; 
 scalar_t__ has_reserved_job (TYPE_2__*) ; 
 int min (int,int) ; 
 int nanoseconds () ; 

__attribute__((used)) static int64
conntickat(Conn *c)
{
    int margin = 0, should_timeout = 0;
    int64 t = INT64_MAX;

    if (conn_waiting(c)) {
        margin = SAFETY_MARGIN;
    }

    if (has_reserved_job(c)) {
        t = connsoonestjob(c)->r.deadline_at - nanoseconds() - margin;
        should_timeout = 1;
    }
    if (c->pending_timeout >= 0) {
        t = min(t, ((int64)c->pending_timeout) * 1000000000);
        should_timeout = 1;
    }

    if (should_timeout) {
        return nanoseconds() + t;
    }
    return 0;
}