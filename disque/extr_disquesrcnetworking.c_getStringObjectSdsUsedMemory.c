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
struct TYPE_5__ {scalar_t__ type; int encoding; int /*<<< orphan*/  ptr; } ;
typedef  TYPE_1__ robj ;

/* Variables and functions */
#define  OBJ_ENCODING_EMBSTR 129 
#define  OBJ_ENCODING_RAW 128 
 scalar_t__ OBJ_STRING ; 
 size_t sdsZmallocSize (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  serverAssertWithInfo (int /*<<< orphan*/ *,TYPE_1__*,int) ; 
 int /*<<< orphan*/  zmalloc_size (TYPE_1__*) ; 

size_t getStringObjectSdsUsedMemory(robj *o) {
    serverAssertWithInfo(NULL,o,o->type == OBJ_STRING);
    switch(o->encoding) {
    case OBJ_ENCODING_RAW: return sdsZmallocSize(o->ptr);
    case OBJ_ENCODING_EMBSTR: return zmalloc_size(o)-sizeof(robj);
    default: return 0; /* Just integer encoding for now. */
    }
}