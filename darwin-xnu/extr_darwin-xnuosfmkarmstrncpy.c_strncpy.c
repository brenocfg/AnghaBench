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

/* Variables and functions */
 int /*<<< orphan*/  memcpy (char*,char const*,size_t const) ; 
 int /*<<< orphan*/  memset (char*,int /*<<< orphan*/ ,size_t) ; 
 size_t strnlen (char const*,size_t) ; 

char *
strncpy(char * dst, const char * src, size_t maxlen) {
    const size_t srclen = strnlen(src, maxlen);
    if (srclen < maxlen) {
        memcpy(dst, src, srclen);
        memset(dst+srclen, 0, maxlen - srclen);
    } else {
        memcpy(dst, src, maxlen);
    }
    return dst;
}