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
struct user_regset {int dummy; } ;
struct thread_struct {int /*<<< orphan*/ * tls_array; } ;
struct task_struct {struct thread_struct thread; } ;

/* Variables and functions */
 int GDT_ENTRY_TLS_ENTRIES ; 
 scalar_t__ desc_empty (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int ia32_tls_active(struct task_struct *target,
		const struct user_regset *regset)
{
	struct thread_struct *t = &target->thread;
	int n = GDT_ENTRY_TLS_ENTRIES;
	while (n > 0 && desc_empty(&t->tls_array[n -1]))
		--n;
	return n;
}