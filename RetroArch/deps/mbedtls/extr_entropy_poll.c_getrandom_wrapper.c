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
 int /*<<< orphan*/  memset (void*,int /*<<< orphan*/ ,size_t) ; 
 int syscall (int /*<<< orphan*/ ,void*,size_t,unsigned int) ; 

__attribute__((used)) static int getrandom_wrapper( void *buf, size_t buflen, unsigned int flags )
{
    /* MemSan cannot understand that the syscall writes to the buffer */
#if defined(__has_feature)
#if __has_feature(memory_sanitizer)
    memset( buf, 0, buflen );
#endif
#endif

    return( syscall( SYS_getrandom, buf, buflen, flags ) );
}