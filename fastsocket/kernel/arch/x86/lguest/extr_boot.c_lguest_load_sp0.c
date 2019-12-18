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
struct tss_struct {int dummy; } ;
struct thread_struct {int /*<<< orphan*/  sp0; } ;

/* Variables and functions */
 int /*<<< orphan*/  LHCALL_SET_STACK ; 
 int PAGE_SIZE ; 
 int THREAD_SIZE ; 
 int __KERNEL_DS ; 
 int /*<<< orphan*/  lazy_hcall3 (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void lguest_load_sp0(struct tss_struct *tss,
			    struct thread_struct *thread)
{
	lazy_hcall3(LHCALL_SET_STACK, __KERNEL_DS | 0x1, thread->sp0,
		   THREAD_SIZE / PAGE_SIZE);
}