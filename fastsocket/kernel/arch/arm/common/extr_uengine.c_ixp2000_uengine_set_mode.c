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
typedef  int u32 ;

/* Variables and functions */
 int /*<<< orphan*/  CC_ENABLE ; 
 int /*<<< orphan*/  CTX_ENABLES ; 
 int /*<<< orphan*/  NN_GET ; 
 int /*<<< orphan*/  NN_PUT ; 
 int /*<<< orphan*/  T_INDEX_BYTE_INDEX ; 
 int /*<<< orphan*/  ixp2000_uengine_csr_write (int,int /*<<< orphan*/ ,int) ; 

void ixp2000_uengine_set_mode(int uengine, u32 mode)
{
	/*
	 * CTL_STR_PAR_EN: unconditionally enable parity checking on
	 * control store.
	 */
	mode |= 0x10000000;
	ixp2000_uengine_csr_write(uengine, CTX_ENABLES, mode);

	/*
	 * Enable updating of condition codes.
	 */
	ixp2000_uengine_csr_write(uengine, CC_ENABLE, 0x00002000);

	/*
	 * Initialise other per-microengine registers.
	 */
	ixp2000_uengine_csr_write(uengine, NN_PUT, 0x00);
	ixp2000_uengine_csr_write(uengine, NN_GET, 0x00);
	ixp2000_uengine_csr_write(uengine, T_INDEX_BYTE_INDEX, 0);
}