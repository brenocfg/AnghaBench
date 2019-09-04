#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {scalar_t__ ptr; } ;
typedef  TYPE_1__ robj ;
typedef  int /*<<< orphan*/  client ;
struct TYPE_6__ {int /*<<< orphan*/ * bulkhdr; } ;

/* Variables and functions */
 size_t OBJ_SHARED_BULKHDR_LEN ; 
 int /*<<< orphan*/  addReply (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  addReplyLongLongWithPrefix (int /*<<< orphan*/ *,size_t,char) ; 
 scalar_t__ sdsEncodedObject (TYPE_1__*) ; 
 size_t sdslen (scalar_t__) ; 
 TYPE_2__ shared ; 

void addReplyBulkLen(client *c, robj *obj) {
    size_t len;

    if (sdsEncodedObject(obj)) {
        len = sdslen(obj->ptr);
    } else {
        long n = (long)obj->ptr;

        /* Compute how many bytes will take this integer as a radix 10 string */
        len = 1;
        if (n < 0) {
            len++;
            n = -n;
        }
        while((n = n/10) != 0) {
            len++;
        }
    }

    if (len < OBJ_SHARED_BULKHDR_LEN)
        addReply(c,shared.bulkhdr[len]);
    else
        addReplyLongLongWithPrefix(c,len,'$');
}