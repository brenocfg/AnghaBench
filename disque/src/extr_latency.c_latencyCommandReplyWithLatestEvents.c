#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct latencyTimeSeries {int idx; int /*<<< orphan*/  max; TYPE_1__* samples; } ;
typedef  int /*<<< orphan*/  dictIterator ;
typedef  int /*<<< orphan*/  dictEntry ;
typedef  int /*<<< orphan*/  client ;
struct TYPE_4__ {int /*<<< orphan*/  latency_events; } ;
struct TYPE_3__ {int /*<<< orphan*/  latency; int /*<<< orphan*/  time; } ;

/* Variables and functions */
 int LATENCY_TS_LEN ; 
 int /*<<< orphan*/  addReplyBulkCString (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  addReplyLongLong (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  addReplyMultiBulkLen (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/ * dictGetIterator (int /*<<< orphan*/ ) ; 
 char* dictGetKey (int /*<<< orphan*/ *) ; 
 struct latencyTimeSeries* dictGetVal (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * dictNext (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dictReleaseIterator (int /*<<< orphan*/ *) ; 
 int dictSize (int /*<<< orphan*/ ) ; 
 TYPE_2__ server ; 

void latencyCommandReplyWithLatestEvents(client *c) {
    dictIterator *di;
    dictEntry *de;

    addReplyMultiBulkLen(c,dictSize(server.latency_events));
    di = dictGetIterator(server.latency_events);
    while((de = dictNext(di)) != NULL) {
        char *event = dictGetKey(de);
        struct latencyTimeSeries *ts = dictGetVal(de);
        int last = (ts->idx + LATENCY_TS_LEN - 1) % LATENCY_TS_LEN;

        addReplyMultiBulkLen(c,4);
        addReplyBulkCString(c,event);
        addReplyLongLong(c,ts->samples[last].time);
        addReplyLongLong(c,ts->samples[last].latency);
        addReplyLongLong(c,ts->max);
    }
    dictReleaseIterator(di);
}