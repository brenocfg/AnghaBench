#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/ * sds ;

/* Variables and functions */
 int /*<<< orphan*/  memset (int /*<<< orphan*/ ,int /*<<< orphan*/ ,size_t) ; 
 int /*<<< orphan*/ * sdsMakeRoomFor (int /*<<< orphan*/ *,size_t) ; 
 size_t sdslen (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sdssetlen (int /*<<< orphan*/ *,size_t) ; 

sds sdsgrowzero(sds s, size_t len) {
    size_t curlen = sdslen(s);

    if (len <= curlen) return s;
    s = sdsMakeRoomFor(s,len-curlen);
    if (s == NULL) return NULL;

    /* Make sure added region doesn't contain garbage */
    memset(s+curlen,0,(len-curlen+1)); /* also set trailing \0 byte */
    sdssetlen(s, len);
    return s;
}