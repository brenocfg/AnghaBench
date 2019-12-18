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
typedef  int /*<<< orphan*/  uint32_t ;
struct x86_fx_thread_state {int dummy; } ;

/* Variables and functions */

__attribute__((used)) static inline void xrstor64(struct x86_fx_thread_state *a, uint32_t rfbm) {
	__asm__ __volatile__("xrstor64 %0" ::  "m" (*a), "a"(rfbm), "d"(0));
}