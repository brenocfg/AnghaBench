#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
struct TYPE_6__ {TYPE_1__* ctx; } ;
typedef  TYPE_2__ atom_exec_context ;
struct TYPE_5__ {int /*<<< orphan*/  fb_base; } ;

/* Variables and functions */
 int /*<<< orphan*/  SDEBUG (char*) ; 
 int /*<<< orphan*/  U8 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  atom_get_src (TYPE_2__*,int /*<<< orphan*/ ,int*) ; 

__attribute__((used)) static void atom_op_setfbbase(atom_exec_context *ctx, int *ptr, int arg)
{
	uint8_t attr = U8((*ptr)++);
	SDEBUG("   fb_base: ");
	ctx->ctx->fb_base = atom_get_src(ctx, attr, ptr);
}