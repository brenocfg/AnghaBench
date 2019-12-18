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
 int /*<<< orphan*/  SCE_GXM_STENCIL_FUNC_ALWAYS ; 
 int /*<<< orphan*/  SCE_GXM_STENCIL_OP_KEEP ; 
 int /*<<< orphan*/  _vita2d_context ; 
 scalar_t__ clipping_enabled ; 
 int /*<<< orphan*/  sceGxmSetFrontStencilFunc (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int) ; 

void vita2d_disable_clipping()
{
	clipping_enabled = 0;
	sceGxmSetFrontStencilFunc(
			_vita2d_context,
			SCE_GXM_STENCIL_FUNC_ALWAYS,
			SCE_GXM_STENCIL_OP_KEEP,
			SCE_GXM_STENCIL_OP_KEEP,
			SCE_GXM_STENCIL_OP_KEEP,
			0xFF,
			0xFF);
}