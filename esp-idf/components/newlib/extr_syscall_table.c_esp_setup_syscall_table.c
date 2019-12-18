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
 int /*<<< orphan*/ * _GLOBAL_REENT ; 
 int /*<<< orphan*/ ** environ ; 
 int /*<<< orphan*/ ** malloc (int) ; 
 int /*<<< orphan*/  s_reent ; 
 int /*<<< orphan*/  s_stub_table ; 
 int /*<<< orphan*/ * syscall_table_ptr_app ; 
 int /*<<< orphan*/ * syscall_table_ptr_pro ; 

void esp_setup_syscall_table(void)
{
    syscall_table_ptr_pro = &s_stub_table;
    syscall_table_ptr_app = &s_stub_table;
    _GLOBAL_REENT = &s_reent;
    environ = malloc(sizeof(char*));
    environ[0] = NULL;
}