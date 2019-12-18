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
typedef  int /*<<< orphan*/  Q68WriteFunc ;
typedef  int /*<<< orphan*/  M68K_WRITE ;

/* Variables and functions */
 int /*<<< orphan*/  q68_set_writew_func (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * real_writew ; 
 int /*<<< orphan*/  state ; 
 int /*<<< orphan*/ * writew_trampoline ; 

__attribute__((used)) static void m68kq68_set_writew(M68K_WRITE *func)
{
#ifdef NEED_TRAMPOLINE
    real_writew = func;
    q68_set_writew_func(state, writew_trampoline);
#else
    q68_set_writew_func(state, (Q68WriteFunc *)func);
#endif
}