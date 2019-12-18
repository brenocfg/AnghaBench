#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int refcount; int type; } ;
typedef  TYPE_1__ robj ;

/* Variables and functions */
#define  OBJ_STRING 128 
 int /*<<< orphan*/  freeStringObject (TYPE_1__*) ; 
 int /*<<< orphan*/  serverPanic (char*) ; 
 int /*<<< orphan*/  zfree (TYPE_1__*) ; 

void decrRefCount(robj *o) {
    if (o->refcount <= 0) serverPanic("decrRefCount against refcount <= 0");
    if (o->refcount == 1) {
        switch(o->type) {
        case OBJ_STRING: freeStringObject(o); break;
        default: serverPanic("Unknown object type"); break;
        }
        zfree(o);
    } else {
        o->refcount--;
    }
}