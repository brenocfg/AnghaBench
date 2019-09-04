#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  sds ;
struct TYPE_7__ {scalar_t__ ptr; } ;
typedef  TYPE_1__ robj ;
struct TYPE_8__ {int argc; int /*<<< orphan*/ * argv; } ;
typedef  TYPE_2__ client ;
struct TYPE_9__ {TYPE_2__* current_client; } ;

/* Variables and functions */
 int /*<<< orphan*/  LL_WARNING ; 
 int /*<<< orphan*/  catClientInfoString (int /*<<< orphan*/ ,TYPE_2__*) ; 
 int /*<<< orphan*/  decrRefCount (TYPE_1__*) ; 
 TYPE_1__* getDecodedObject (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sdsempty () ; 
 int /*<<< orphan*/  sdsfree (int /*<<< orphan*/ ) ; 
 TYPE_3__ server ; 
 int /*<<< orphan*/  serverLog (int /*<<< orphan*/ ,char*,...) ; 

void logCurrentClient(void) {
    if (server.current_client == NULL) return;

    client *cc = server.current_client;
    sds client;
    int j;

    serverLog(LL_WARNING, "--- CURRENT CLIENT INFO");
    client = catClientInfoString(sdsempty(),cc);
    serverLog(LL_WARNING,"client: %s", client);
    sdsfree(client);
    for (j = 0; j < cc->argc; j++) {
        robj *decoded;

        decoded = getDecodedObject(cc->argv[j]);
        serverLog(LL_WARNING,"argv[%d]: '%s'", j, (char*)decoded->ptr);
        decrRefCount(decoded);
    }
}