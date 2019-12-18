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
 int /*<<< orphan*/  _libkernel_memmove (char*,char const*,size_t const) ; 
 size_t _libkernel_strlen (char const*) ; 

__attribute__((visibility("hidden")))
size_t
_libkernel_strlcpy(char * restrict dst, const char * restrict src, size_t maxlen) {
    const size_t srclen = _libkernel_strlen(src);
    if (srclen < maxlen) {
        _libkernel_memmove(dst, src, srclen+1);
    } else if (maxlen != 0) {
        _libkernel_memmove(dst, src, maxlen-1);
        dst[maxlen-1] = '\0';
    }
    return srclen;
}