#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  sds ;
struct TYPE_5__ {int /*<<< orphan*/  querybuf; int /*<<< orphan*/  flags; } ;
typedef  TYPE_1__ client ;
struct TYPE_6__ {scalar_t__ verbosity; } ;

/* Variables and functions */
 int /*<<< orphan*/  CLIENT_CLOSE_AFTER_REPLY ; 
 scalar_t__ LL_VERBOSE ; 
 int /*<<< orphan*/  catClientInfoString (int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  sdsempty () ; 
 int /*<<< orphan*/  sdsfree (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sdsrange (int /*<<< orphan*/ ,int,int) ; 
 TYPE_3__ server ; 
 int /*<<< orphan*/  serverLog (scalar_t__,char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void setProtocolError(client *c, int pos) {
    if (server.verbosity <= LL_VERBOSE) {
        sds client = catClientInfoString(sdsempty(),c);
        serverLog(LL_VERBOSE,
            "Protocol error from client: %s", client);
        sdsfree(client);
    }
    c->flags |= CLIENT_CLOSE_AFTER_REPLY;
    sdsrange(c->querybuf,pos,-1);
}