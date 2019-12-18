#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct thread_struct {int /*<<< orphan*/ * tls_array; } ;
struct TYPE_2__ {struct thread_struct thread; } ;

/* Variables and functions */
 int ESRCH ; 
 int GDT_ENTRY_TLS_ENTRIES ; 
 int GDT_ENTRY_TLS_MIN ; 
 TYPE_1__* current ; 
 scalar_t__ desc_empty (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int get_free_idx(void)
{
	struct thread_struct *t = &current->thread;
	int idx;

	for (idx = 0; idx < GDT_ENTRY_TLS_ENTRIES; idx++)
		if (desc_empty(&t->tls_array[idx]))
			return idx + GDT_ENTRY_TLS_MIN;
	return -ESRCH;
}