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
 int /*<<< orphan*/  SYS_getrandom ; 
 int /*<<< orphan*/  abort () ; 
 int /*<<< orphan*/  arc4random_buf (void*,size_t) ; 
 scalar_t__ syscall (int /*<<< orphan*/ ,void*,int,int /*<<< orphan*/ ) ; 

void uc_randombytes_buf(void *buf, size_t len)
{
#ifdef __linux__
    if ((size_t) syscall(SYS_getrandom, buf, (int) len, 0) != len) {
        abort();
    }
#else
    arc4random_buf(buf, len);
#endif
}