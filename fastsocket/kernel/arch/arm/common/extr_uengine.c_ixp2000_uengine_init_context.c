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

/* Variables and functions */
 int /*<<< orphan*/  CSR_CTX_POINTER ; 
 int /*<<< orphan*/  INDIRECT_CTX_SIG_EVENTS ; 
 int /*<<< orphan*/  INDIRECT_CTX_STS ; 
 int /*<<< orphan*/  INDIRECT_CTX_WAKEUP_EVENTS ; 
 int /*<<< orphan*/  ixp2000_uengine_csr_write (int,int /*<<< orphan*/ ,int) ; 

void ixp2000_uengine_init_context(int uengine, int context, int pc)
{
	/*
	 * Select the right context for indirect access.
	 */
	ixp2000_uengine_csr_write(uengine, CSR_CTX_POINTER, context);

	/*
	 * Initialise signal masks to immediately go to Ready state.
	 */
	ixp2000_uengine_csr_write(uengine, INDIRECT_CTX_SIG_EVENTS, 1);
	ixp2000_uengine_csr_write(uengine, INDIRECT_CTX_WAKEUP_EVENTS, 1);

	/*
	 * Set program counter.
	 */
	ixp2000_uengine_csr_write(uengine, INDIRECT_CTX_STS, pc);
}