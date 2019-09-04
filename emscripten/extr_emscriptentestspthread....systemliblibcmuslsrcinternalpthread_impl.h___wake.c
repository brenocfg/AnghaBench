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
 int /*<<< orphan*/  ENOSYS ; 
 int FUTEX_WAKE ; 
 int INT_MAX ; 
 int /*<<< orphan*/  SYS_futex ; 
 int /*<<< orphan*/  __syscall (int /*<<< orphan*/ ,void volatile*,int,int) ; 

__attribute__((used)) static inline void __wake(volatile void *addr, int cnt, int priv)
{
	if (priv) priv = 128;
	if (cnt<0) cnt = INT_MAX;
#ifdef __EMSCRIPTEN__
	emscripten_futex_wake(addr, (cnt)<0?INT_MAX:(cnt));
#else
	__syscall(SYS_futex, addr, FUTEX_WAKE|priv, cnt) != -ENOSYS ||
	__syscall(SYS_futex, addr, FUTEX_WAKE, cnt);
#endif
}