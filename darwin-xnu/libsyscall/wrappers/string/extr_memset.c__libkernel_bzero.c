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
 int /*<<< orphan*/  _libkernel_memset (void*,int /*<<< orphan*/ ,size_t) ; 

__attribute__((visibility("hidden")))
void
_libkernel_bzero(void *dst0, size_t length)
{
    return (void)_libkernel_memset(dst0, 0, length);
}