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
char *
_libkernel_strcpy(char * restrict dst, const char * restrict src) {
	const size_t length = _libkernel_strlen(src);
    //  The stpcpy() and strcpy() functions copy the string src to dst
    //  (including the terminating '\0' character).
    _libkernel_memmove(dst, src, length+1);
    //  The strcpy() and strncpy() functions return dst.
    return dst;
}