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
struct TYPE_6__ {unsigned char* ptr; scalar_t__ encoding; } ;
typedef  TYPE_1__ robj ;

/* Variables and functions */
 scalar_t__ OBJ_ENCODING_INT ; 
 int /*<<< orphan*/  decrRefCount (TYPE_1__*) ; 
 unsigned int dictGenHashFunction (unsigned char*,int) ; 
 TYPE_1__* getDecodedObject (TYPE_1__*) ; 
 int ll2string (char*,int,long) ; 
 scalar_t__ sdsEncodedObject (TYPE_1__*) ; 
 int sdslen (int /*<<< orphan*/ ) ; 

unsigned int dictEncObjHash(const void *key) {
    robj *o = (robj*) key;

    if (sdsEncodedObject(o)) {
        return dictGenHashFunction(o->ptr, sdslen((sds)o->ptr));
    } else {
        if (o->encoding == OBJ_ENCODING_INT) {
            char buf[32];
            int len;

            len = ll2string(buf,32,(long)o->ptr);
            return dictGenHashFunction((unsigned char*)buf, len);
        } else {
            unsigned int hash;

            o = getDecodedObject(o);
            hash = dictGenHashFunction(o->ptr, sdslen((sds)o->ptr));
            decrRefCount(o);
            return hash;
        }
    }
}