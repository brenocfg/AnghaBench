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
struct task_struct {int dummy; } ;
typedef  int /*<<< orphan*/  atomic_t ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  THREAD_SIZE ; 
 int /*<<< orphan*/  atomic_set (int /*<<< orphan*/ *,int) ; 
 struct task_struct* kmalloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

struct task_struct *alloc_task_struct(void)
{
	struct task_struct *p = kmalloc(THREAD_SIZE, GFP_KERNEL);
	if (p)
		atomic_set((atomic_t *)(p+1), 1);
	return p;
}