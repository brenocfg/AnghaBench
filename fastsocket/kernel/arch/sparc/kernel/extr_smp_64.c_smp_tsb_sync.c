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
struct mm_struct {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  mm_cpumask (struct mm_struct*) ; 
 int /*<<< orphan*/  smp_call_function_many (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct mm_struct*,int) ; 
 int /*<<< orphan*/  tsb_sync ; 

void smp_tsb_sync(struct mm_struct *mm)
{
	smp_call_function_many(mm_cpumask(mm), tsb_sync, mm, 1);
}