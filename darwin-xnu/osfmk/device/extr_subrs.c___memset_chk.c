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
 void* memset (void*,int,size_t) ; 
 int /*<<< orphan*/  panic (char*,void*,int,size_t,size_t) ; 

void *
__memset_chk(void *dst, int c, size_t s, size_t chk_size)
{
    if (__improbable(chk_size < s))
        panic("__memset_chk object size check failed: dst %p, c %c, (%zu < %zu)", dst, c, chk_size, s);
    return memset(dst, c, s);
}