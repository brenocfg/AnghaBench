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
struct vm_area_struct {int dummy; } ;
struct mm_struct {int /*<<< orphan*/  flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  MMF_COMPAT ; 
 struct vm_area_struct gate_vma ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

struct vm_area_struct *get_gate_vma(struct mm_struct *mm)
{
#ifdef CONFIG_IA32_EMULATION
	if (!mm || test_bit(MMF_COMPAT, &mm->flags))
		return NULL;
#endif
	return &gate_vma;
}