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
 int /*<<< orphan*/  run () ; 

void __start(void)
{ 
#if defined(MIPS) || defined(MIPSEL)
    __asm(
        ".set noreorder\n"
        "move $0, $31\n"
        "bal 10f\n"
        "nop\n"
        "10:\n.cpload $31\n"
        "move $31, $0\n"
        ".set reorder\n"
    );
#endif
    run();
}