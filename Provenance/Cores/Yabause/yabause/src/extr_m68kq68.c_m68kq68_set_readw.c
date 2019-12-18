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
typedef  int /*<<< orphan*/  Q68ReadFunc ;
typedef  int /*<<< orphan*/  M68K_READ ;

/* Variables and functions */
 int /*<<< orphan*/  q68_set_readw_func (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * readw_trampoline ; 
 int /*<<< orphan*/ * real_readw ; 
 int /*<<< orphan*/  state ; 

__attribute__((used)) static void m68kq68_set_readw(M68K_READ *func)
{
#ifdef NEED_TRAMPOLINE
    real_readw = func;
    q68_set_readw_func(state, readw_trampoline);
#else
    q68_set_readw_func(state, (Q68ReadFunc *)func);
#endif
}