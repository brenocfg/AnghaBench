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
typedef  unsigned int uint64_t ;

/* Variables and functions */
 int /*<<< orphan*/  SYS_sleep_thread ; 
 int /*<<< orphan*/  syscall2 (int /*<<< orphan*/ ,int,int) ; 

unsigned int sleep( unsigned int seconds ) {
    uint64_t time;

    time = seconds * 1000000;

    syscall2( SYS_sleep_thread, ( int )&time, ( int )NULL );

    return 0;
}