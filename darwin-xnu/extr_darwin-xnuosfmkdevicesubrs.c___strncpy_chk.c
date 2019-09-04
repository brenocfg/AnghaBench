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
 scalar_t__ __improbable (int) ; 
 int /*<<< orphan*/  panic (char*,char*,char*,size_t,size_t) ; 
 char* strncpy (char*,char*,size_t) ; 

char *
__strncpy_chk (char *restrict dst, char *restrict src,
               size_t len, size_t chk_size)
{
    if (__improbable(chk_size < len)) {
        panic("__strncpy_chk object size check failed: dst %p, src %p, (%zu < %zu)", dst, src, chk_size, len);
    }
    return strncpy(dst, src, len);
}