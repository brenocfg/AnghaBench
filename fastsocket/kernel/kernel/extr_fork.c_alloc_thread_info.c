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
struct thread_info {int dummy; } ;
struct task_struct {int dummy; } ;
typedef  int gfp_t ;

/* Variables and functions */
 int GFP_KERNEL ; 
 int /*<<< orphan*/  THREAD_SIZE_ORDER ; 
 int __GFP_ZERO ; 
 scalar_t__ __get_free_pages (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline struct thread_info *alloc_thread_info(struct task_struct *tsk)
{
#ifdef CONFIG_DEBUG_STACK_USAGE
	gfp_t mask = GFP_KERNEL | __GFP_ZERO;
#else
	gfp_t mask = GFP_KERNEL;
#endif
	return (struct thread_info *)__get_free_pages(mask, THREAD_SIZE_ORDER);
}