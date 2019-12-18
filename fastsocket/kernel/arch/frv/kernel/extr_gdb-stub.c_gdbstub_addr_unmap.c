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
 int /*<<< orphan*/  __saved_damlr ; 
 int /*<<< orphan*/  __saved_dampr ; 
 int /*<<< orphan*/  __set_DAMLR (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  __set_DAMPR (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline void gdbstub_addr_unmap(void)
{
#ifdef CONFIG_MMU
	__set_DAMPR(2, __saved_dampr);
	__set_DAMLR(2, __saved_damlr);
#endif
}