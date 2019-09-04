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
typedef  int time_t ;
struct TYPE_4__ {int lastinteraction; int querybuf_peak; int /*<<< orphan*/  querybuf; } ;
typedef  TYPE_1__ client ;
struct TYPE_5__ {int unixtime; } ;

/* Variables and functions */
 size_t PROTO_MBULK_BIG_ARG ; 
 size_t sdsAllocSize (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sdsRemoveFreeSpace (int /*<<< orphan*/ ) ; 
 int sdsavail (int /*<<< orphan*/ ) ; 
 TYPE_2__ server ; 

int clientsCronResizeQueryBuffer(client *c) {
    size_t querybuf_size = sdsAllocSize(c->querybuf);
    time_t idletime = server.unixtime - c->lastinteraction;

    /* There are two conditions to resize the query buffer:
     * 1) Query buffer is > BIG_ARG and too big for latest peak.
     * 2) Client is inactive and the buffer is bigger than 1k. */
    if (((querybuf_size > PROTO_MBULK_BIG_ARG) &&
         (querybuf_size/(c->querybuf_peak+1)) > 2) ||
         (querybuf_size > 1024 && idletime > 2))
    {
        /* Only resize the query buffer if it is actually wasting space. */
        if (sdsavail(c->querybuf) > 1024) {
            c->querybuf = sdsRemoveFreeSpace(c->querybuf);
        }
    }
    /* Reset the peak again to capture the peak memory usage in the next
     * cycle. */
    c->querybuf_peak = 0;
    return 0;
}