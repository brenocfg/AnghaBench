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
typedef  int u8 ;
typedef  int u32 ;

/* Variables and functions */
 int /*<<< orphan*/  CTX_ENABLES ; 
 int ixp2000_uengine_csr_read (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ixp2000_uengine_csr_write (int,int /*<<< orphan*/ ,int) ; 

void ixp2000_uengine_start_contexts(int uengine, u8 ctx_mask)
{
	u32 mask;

	/*
	 * Enable the specified context to go to Executing state.
	 */
	mask = ixp2000_uengine_csr_read(uengine, CTX_ENABLES);
	mask |= ctx_mask << 8;
	ixp2000_uengine_csr_write(uengine, CTX_ENABLES, mask);
}