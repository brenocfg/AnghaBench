#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  sds ;
struct TYPE_6__ {int reply_bytes; int flags; } ;
typedef  TYPE_1__ client ;

/* Variables and functions */
 int CLIENT_CLOSE_ASAP ; 
 int /*<<< orphan*/  LL_WARNING ; 
 int SIZE_MAX ; 
 int /*<<< orphan*/  catClientInfoString (int /*<<< orphan*/ ,TYPE_1__*) ; 
 scalar_t__ checkClientOutputBufferLimits (TYPE_1__*) ; 
 int /*<<< orphan*/  freeClientAsync (TYPE_1__*) ; 
 int /*<<< orphan*/  sdsempty () ; 
 int /*<<< orphan*/  sdsfree (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  serverAssert (int) ; 
 int /*<<< orphan*/  serverLog (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 

void asyncCloseClientOnOutputBufferLimitReached(client *c) {
    serverAssert(c->reply_bytes < SIZE_MAX-(1024*64));
    if (c->reply_bytes == 0 || c->flags & CLIENT_CLOSE_ASAP) return;
    if (checkClientOutputBufferLimits(c)) {
        sds client = catClientInfoString(sdsempty(),c);

        freeClientAsync(c);
        serverLog(LL_WARNING,"Client %s scheduled to be closed ASAP for overcoming of output buffer limits.", client);
        sdsfree(client);
    }
}