#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {unsigned int kvm_seq; } ;
struct mm_struct {TYPE_2__ context; } ;
typedef  int /*<<< orphan*/  pgd_t ;
struct TYPE_4__ {unsigned int kvm_seq; } ;
struct TYPE_6__ {TYPE_1__ context; } ;

/* Variables and functions */
 int /*<<< orphan*/  VMALLOC_END ; 
 int /*<<< orphan*/  VMALLOC_START ; 
 TYPE_3__ init_mm ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int pgd_index (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pgd_offset (struct mm_struct*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pgd_offset_k (int /*<<< orphan*/ ) ; 

void __check_kvm_seq(struct mm_struct *mm)
{
	unsigned int seq;

	do {
		seq = init_mm.context.kvm_seq;
		memcpy(pgd_offset(mm, VMALLOC_START),
		       pgd_offset_k(VMALLOC_START),
		       sizeof(pgd_t) * (pgd_index(VMALLOC_END) -
					pgd_index(VMALLOC_START)));
		mm->context.kvm_seq = seq;
	} while (seq != init_mm.context.kvm_seq);
}