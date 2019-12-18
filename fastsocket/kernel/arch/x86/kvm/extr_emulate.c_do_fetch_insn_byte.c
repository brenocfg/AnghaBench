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
typedef  int /*<<< orphan*/  u8 ;
struct x86_emulate_ops {int (* fetch ) (unsigned long,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ;} ;
struct fetch_cache {unsigned long start; unsigned long end; int /*<<< orphan*/ * data; } ;
struct TYPE_2__ {struct fetch_cache fetch; } ;
struct x86_emulate_ctxt {int /*<<< orphan*/  vcpu; TYPE_1__ decode; } ;

/* Variables and functions */
 scalar_t__ PAGE_SIZE ; 
 int X86EMUL_CONTINUE ; 
 int min (unsigned long,scalar_t__) ; 
 scalar_t__ offset_in_page (unsigned long) ; 
 int stub1 (unsigned long,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int do_fetch_insn_byte(struct x86_emulate_ctxt *ctxt,
			      struct x86_emulate_ops *ops,
			      unsigned long linear, u8 *dest)
{
	struct fetch_cache *fc = &ctxt->decode.fetch;
	int rc;
	int size;

	if (linear < fc->start || linear >= fc->end) {
		size = min(15UL, PAGE_SIZE - offset_in_page(linear));
		rc = ops->fetch(linear, fc->data, size, ctxt->vcpu, NULL);
		if (rc != X86EMUL_CONTINUE)
			return rc;
		fc->start = linear;
		fc->end = linear + size;
	}
	*dest = fc->data[linear - fc->start];
	return X86EMUL_CONTINUE;
}