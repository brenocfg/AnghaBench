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
 int /*<<< orphan*/ * _REENT ; 
 int /*<<< orphan*/  __sys_state_get () ; 
 int /*<<< orphan*/  __sys_state_up (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  _wrapup_reent (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  libc_globl_reent ; 

void __libc_wrapup()
{
	if(!__sys_state_up(__sys_state_get())) return;
	if(_REENT!=&libc_globl_reent) {
		_wrapup_reent(&libc_globl_reent);
		_REENT = &libc_globl_reent;
	}
}