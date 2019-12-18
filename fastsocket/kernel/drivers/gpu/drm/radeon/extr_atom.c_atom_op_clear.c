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
 int /*<<< orphan*/  SDEBUG (char*) ; 
 int U8 (int /*<<< orphan*/ ) ; 
 int* atom_def_dst ; 
 int /*<<< orphan*/  atom_get_dst (int /*<<< orphan*/ *,int,int,int*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  atom_put_dst (int /*<<< orphan*/ *,int,int,int*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void atom_op_clear(atom_exec_context *ctx, int *ptr, int arg)
{
	uint8_t attr = U8((*ptr)++);
	uint32_t saved;
	int dptr = *ptr;
	attr &= 0x38;
	attr |= atom_def_dst[attr >> 3] << 6;
	atom_get_dst(ctx, arg, attr, ptr, &saved, 0);
	SDEBUG("   dst: ");
	atom_put_dst(ctx, arg, attr, &dptr, 0, saved);
}