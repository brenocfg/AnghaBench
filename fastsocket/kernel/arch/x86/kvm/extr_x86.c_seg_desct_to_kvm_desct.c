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
typedef  int /*<<< orphan*/  u16 ;
struct kvm_segment {int limit; int unusable; scalar_t__ padding; int /*<<< orphan*/  avl; scalar_t__ g; int /*<<< orphan*/  l; int /*<<< orphan*/  s; int /*<<< orphan*/  db; int /*<<< orphan*/  dpl; int /*<<< orphan*/  present; int /*<<< orphan*/  type; int /*<<< orphan*/  selector; int /*<<< orphan*/  base; } ;
struct desc_struct {int /*<<< orphan*/  avl; scalar_t__ g; int /*<<< orphan*/  l; int /*<<< orphan*/  s; int /*<<< orphan*/  d; int /*<<< orphan*/  dpl; int /*<<< orphan*/  p; int /*<<< orphan*/  type; } ;

/* Variables and functions */
 int /*<<< orphan*/  get_desc_base (struct desc_struct*) ; 
 int get_desc_limit (struct desc_struct*) ; 

__attribute__((used)) static void seg_desct_to_kvm_desct(struct desc_struct *seg_desc, u16 selector,
				   struct kvm_segment *kvm_desct)
{
	kvm_desct->base = get_desc_base(seg_desc);
	kvm_desct->limit = get_desc_limit(seg_desc);
	if (seg_desc->g) {
		kvm_desct->limit <<= 12;
		kvm_desct->limit |= 0xfff;
	}
	kvm_desct->selector = selector;
	kvm_desct->type = seg_desc->type;
	kvm_desct->present = seg_desc->p;
	kvm_desct->dpl = seg_desc->dpl;
	kvm_desct->db = seg_desc->d;
	kvm_desct->s = seg_desc->s;
	kvm_desct->l = seg_desc->l;
	kvm_desct->g = seg_desc->g;
	kvm_desct->avl = seg_desc->avl;
	if (!selector)
		kvm_desct->unusable = 1;
	else
		kvm_desct->unusable = 0;
	kvm_desct->padding = 0;
}