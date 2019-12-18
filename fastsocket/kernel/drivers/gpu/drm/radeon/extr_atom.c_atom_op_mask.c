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
typedef  int uint8_t ;
typedef  int /*<<< orphan*/  uint32_t ;
typedef  int /*<<< orphan*/  atom_exec_context ;

/* Variables and functions */
 int /*<<< orphan*/  SDEBUG (char*,...) ; 
 int U8 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  atom_get_dst (int /*<<< orphan*/ *,int,int,int*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  atom_get_src (int /*<<< orphan*/ *,int,int*) ; 
 int /*<<< orphan*/  atom_get_src_direct (int /*<<< orphan*/ *,int,int*) ; 
 int /*<<< orphan*/  atom_put_dst (int /*<<< orphan*/ *,int,int,int*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void atom_op_mask(atom_exec_context *ctx, int *ptr, int arg)
{
	uint8_t attr = U8((*ptr)++);
	uint32_t dst, mask, src, saved;
	int dptr = *ptr;
	SDEBUG("   dst: ");
	dst = atom_get_dst(ctx, arg, attr, ptr, &saved, 1);
	mask = atom_get_src_direct(ctx, ((attr >> 3) & 7), ptr);
	SDEBUG("   mask: 0x%08x", mask);
	SDEBUG("   src: ");
	src = atom_get_src(ctx, attr, ptr);
	dst &= mask;
	dst |= src;
	SDEBUG("   dst: ");
	atom_put_dst(ctx, arg, attr, &dptr, dst, saved);
}