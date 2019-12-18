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
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int uint64 ;
struct TYPE_8__ {int /*<<< orphan*/  pause_ct; int /*<<< orphan*/  total_delete_ct; int /*<<< orphan*/  waiting_ct; int /*<<< orphan*/  total_jobs_ct; int /*<<< orphan*/  buried_ct; int /*<<< orphan*/  reserved_ct; int /*<<< orphan*/  urgent_ct; } ;
struct TYPE_7__ {int /*<<< orphan*/  len; } ;
struct TYPE_6__ {int /*<<< orphan*/  len; } ;
struct TYPE_9__ {int pause; int unpause_at; TYPE_3__ stat; int /*<<< orphan*/  watching_ct; int /*<<< orphan*/  using_ct; TYPE_2__ delay; TYPE_1__ ready; int /*<<< orphan*/  name; } ;
typedef  TYPE_4__ Tube ;

/* Variables and functions */
 char* STATS_TUBE_FMT ; 
 int nanoseconds () ; 
 int snprintf (char*,size_t,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int) ; 

__attribute__((used)) static int
fmt_stats_tube(char *buf, size_t size, Tube *t)
{
    uint64 time_left;

    if (t->pause > 0) {
        time_left = (t->unpause_at - nanoseconds()) / 1000000000;
    } else {
        time_left = 0;
    }
    return snprintf(buf, size, STATS_TUBE_FMT,
            t->name,
            t->stat.urgent_ct,
            t->ready.len,
            t->stat.reserved_ct,
            t->delay.len,
            t->stat.buried_ct,
            t->stat.total_jobs_ct,
            t->using_ct,
            t->watching_ct,
            t->stat.waiting_ct,
            t->stat.total_delete_ct,
            t->stat.pause_ct,
            t->pause / 1000000000,
            time_left);
}