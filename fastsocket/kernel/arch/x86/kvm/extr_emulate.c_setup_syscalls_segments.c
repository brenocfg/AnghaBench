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
struct x86_emulate_ctxt {int /*<<< orphan*/  vcpu; } ;
struct kvm_segment {int g; int limit; int type; int s; int present; int db; scalar_t__ dpl; scalar_t__ base; scalar_t__ unusable; scalar_t__ l; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* get_segment ) (int /*<<< orphan*/ ,struct kvm_segment*,int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  VCPU_SREG_CS ; 
 TYPE_1__* kvm_x86_ops ; 
 int /*<<< orphan*/  memset (struct kvm_segment*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,struct kvm_segment*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline void
setup_syscalls_segments(struct x86_emulate_ctxt *ctxt,
	struct kvm_segment *cs, struct kvm_segment *ss)
{
	memset(cs, 0, sizeof(struct kvm_segment));
	kvm_x86_ops->get_segment(ctxt->vcpu, cs, VCPU_SREG_CS);
	memset(ss, 0, sizeof(struct kvm_segment));

	cs->l = 0;		/* will be adjusted later */
	cs->base = 0;		/* flat segment */
	cs->g = 1;		/* 4kb granularity */
	cs->limit = 0xffffffff;	/* 4GB limit */
	cs->type = 0x0b;	/* Read, Execute, Accessed */
	cs->s = 1;
	cs->dpl = 0;		/* will be adjusted later */
	cs->present = 1;
	cs->db = 1;

	ss->unusable = 0;
	ss->base = 0;		/* flat segment */
	ss->limit = 0xffffffff;	/* 4GB limit */
	ss->g = 1;		/* 4kb granularity */
	ss->s = 1;
	ss->type = 0x03;	/* Read/Write, Accessed */
	ss->db = 1;		/* 32bit stack segment */
	ss->dpl = 0;
	ss->present = 1;
}