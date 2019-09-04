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
struct TYPE_5__ {scalar_t__ type; scalar_t__ encoding; scalar_t__ ptr; } ;
typedef  TYPE_1__ robj ;

/* Variables and functions */
 int C_ERR ; 
 int C_OK ; 
 scalar_t__ ERANGE ; 
 scalar_t__ OBJ_ENCODING_INT ; 
 scalar_t__ OBJ_STRING ; 
 scalar_t__ errno ; 
 scalar_t__ isspace (char) ; 
 scalar_t__ sdsEncodedObject (TYPE_1__*) ; 
 int /*<<< orphan*/  serverAssertWithInfo (int /*<<< orphan*/ *,TYPE_1__*,int) ; 
 int /*<<< orphan*/  serverPanic (char*) ; 
 long long strtoll (scalar_t__,char**,int) ; 

int getLongLongFromObject(robj *o, long long *target) {
    long long value;
    char *eptr;

    if (o == NULL) {
        value = 0;
    } else {
        serverAssertWithInfo(NULL,o,o->type == OBJ_STRING);
        if (sdsEncodedObject(o)) {
            errno = 0;
            value = strtoll(o->ptr, &eptr, 10);
            if (isspace(((char*)o->ptr)[0]) || eptr[0] != '\0' ||
                errno == ERANGE)
                return C_ERR;
        } else if (o->encoding == OBJ_ENCODING_INT) {
            value = (long)o->ptr;
        } else {
            serverPanic("Unknown string encoding");
        }
    }
    if (target) *target = value;
    return C_OK;
}