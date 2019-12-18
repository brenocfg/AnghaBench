#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  val; } ;
struct decode_cache {TYPE_1__ src; } ;
struct x86_emulate_ctxt {int /*<<< orphan*/  vcpu; struct decode_cache decode; } ;
struct kvm_segment {int /*<<< orphan*/  selector; } ;
struct TYPE_4__ {int /*<<< orphan*/  (* get_segment ) (int /*<<< orphan*/ ,struct kvm_segment*,int) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  emulate_push (struct x86_emulate_ctxt*) ; 
 TYPE_2__* kvm_x86_ops ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,struct kvm_segment*,int) ; 

__attribute__((used)) static void emulate_push_sreg(struct x86_emulate_ctxt *ctxt, int seg)
{
	struct decode_cache *c = &ctxt->decode;
	struct kvm_segment segment;

	kvm_x86_ops->get_segment(ctxt->vcpu, &segment, seg);

	c->src.val = segment.selector;
	emulate_push(ctxt);
}