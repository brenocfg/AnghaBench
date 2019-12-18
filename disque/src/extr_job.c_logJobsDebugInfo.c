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
struct TYPE_4__ {scalar_t__ etime; scalar_t__ qtime; scalar_t__ awakeme; scalar_t__ flags; scalar_t__ repl; scalar_t__ delay; scalar_t__ retry; scalar_t__ state; int /*<<< orphan*/  id; } ;
typedef  TYPE_1__ job ;
struct TYPE_5__ {scalar_t__ mstime; } ;

/* Variables and functions */
 int /*<<< orphan*/  JOB_ID_LEN ; 
 scalar_t__ mstime () ; 
 TYPE_2__ server ; 
 int /*<<< orphan*/  serverLog (int,char*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int,int,int,int,long long,long long,scalar_t__,long long,scalar_t__,scalar_t__) ; 

void logJobsDebugInfo(int level, char *msg, job *j) {
    serverLog(level,
        "%s %.*s: state=%d retry=%d delay=%d replicate=%d flags=%d now=%lld cached_now=%lld awake=%lld (%lld) qtime=%lld etime=%lld",
        msg,
        JOB_ID_LEN, j->id,
        (int)j->state,
        (int)j->retry,
        (int)j->delay,
        (int)j->repl,
        (int)j->flags,
        (long long)mstime(),
        (long long)server.mstime,
        (long long)j->awakeme-mstime(),
        (long long)j->awakeme,
        (long long)j->qtime-mstime(),
        (long long)j->etime*1000-mstime()
        );
}