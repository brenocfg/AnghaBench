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
 int /*<<< orphan*/  _Exit (int) ; 

int main(int artc, char *argv[]) {
#if defined(__x86_64__)
    asm volatile ("andq  $0xfffffffffffffff0, %rsp\n");
#elif defined(__i386__)
    asm volatile ("andl  $0xfffffff0, %esp\n");
#elif defined(__arm__) || defined(__arm64__)
	asm volatile ("");
#else
#error Unsupported architecture
#endif
    _Exit(42);
}