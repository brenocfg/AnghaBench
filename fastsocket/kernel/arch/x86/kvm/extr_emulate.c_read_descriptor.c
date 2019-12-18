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
struct x86_emulate_ops {int (* read_std ) (unsigned long,unsigned long*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ;} ;
struct x86_emulate_ctxt {int /*<<< orphan*/  vcpu; } ;

/* Variables and functions */
 int X86EMUL_CONTINUE ; 
 int stub1 (unsigned long,unsigned long*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int stub2 (unsigned long,unsigned long*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int read_descriptor(struct x86_emulate_ctxt *ctxt,
			   struct x86_emulate_ops *ops,
			   void *ptr,
			   u16 *size, unsigned long *address, int op_bytes)
{
	int rc;

	if (op_bytes == 2)
		op_bytes = 3;
	*address = 0;
	rc = ops->read_std((unsigned long)ptr, (unsigned long *)size, 2,
			   ctxt->vcpu, NULL);
	if (rc != X86EMUL_CONTINUE)
		return rc;
	rc = ops->read_std((unsigned long)ptr + 2, address, op_bytes,
			   ctxt->vcpu, NULL);
	return rc;
}