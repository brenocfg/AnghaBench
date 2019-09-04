#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int sds ;
struct TYPE_4__ {int type; int encoding; int refcount; int /*<<< orphan*/  ptr; } ;
typedef  TYPE_1__ robj ;

/* Variables and functions */
 int /*<<< orphan*/  LL_WARNING ; 
 scalar_t__ OBJ_STRING ; 
 scalar_t__ sdsEncodedObject (TYPE_1__*) ; 
 int sdscatrepr (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  sdsempty () ; 
 int /*<<< orphan*/  sdsfree (int) ; 
 int sdslen (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  serverLog (int /*<<< orphan*/ ,char*,int) ; 

void serverLogObjectDebugInfo(robj *o) {
    serverLog(LL_WARNING,"Object type: %u", o->type);
    serverLog(LL_WARNING,"Object encoding: %u", o->encoding);
    serverLog(LL_WARNING,"Object refcount: %d", o->refcount);
    if (o->type == OBJ_STRING && sdsEncodedObject(o)) {
        serverLog(LL_WARNING,"Object raw string len: %zu", sdslen(o->ptr));
        if (sdslen(o->ptr) < 4096) {
            sds repr = sdscatrepr(sdsempty(),o->ptr,sdslen(o->ptr));
            serverLog(LL_WARNING,"Object raw string content: %s", repr);
            sdsfree(repr);
        }
    }
}