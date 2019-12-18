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
typedef  int /*<<< orphan*/  uint32_t ;
typedef  int /*<<< orphan*/ * sds ;
typedef  int /*<<< orphan*/  count ;

/* Variables and functions */
 int /*<<< orphan*/  intrev32ifbe (size_t) ; 
 int /*<<< orphan*/  memcpy (char*,int /*<<< orphan*/ *,size_t) ; 
 size_t sdslen (int /*<<< orphan*/ *) ; 

char *serializeSdsString(char *p, sds s) {
    size_t len = s ? sdslen(s) : 0;
    uint32_t count = intrev32ifbe(len);

    memcpy(p,&count,sizeof(count));
    if (s) memcpy(p+sizeof(count),s,len);
    return p + sizeof(count) + len;
}