#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  textureTint; int /*<<< orphan*/  texture; int /*<<< orphan*/  color; } ;
typedef  TYPE_1__ vita2d_fragment_programs ;
typedef  int /*<<< orphan*/  SceGxmMultisampleMode ;
typedef  int /*<<< orphan*/  SceGxmBlendInfo ;

/* Variables and functions */
 int /*<<< orphan*/  SCE_GXM_OUTPUT_REGISTER_FORMAT_UCHAR4 ; 
 int /*<<< orphan*/  VITA2D_DEBUG (char*,int) ; 
 int /*<<< orphan*/  colorFragmentProgramId ; 
 int /*<<< orphan*/  colorVertexProgramGxp ; 
 int sceGxmShaderPatcherCreateFragmentProgram (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/  const*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  shaderPatcher ; 
 int /*<<< orphan*/  textureFragmentProgramId ; 
 int /*<<< orphan*/  textureTintFragmentProgramId ; 
 int /*<<< orphan*/  textureVertexProgramGxp ; 

__attribute__((used)) static void _vita2d_make_fragment_programs(vita2d_fragment_programs *out,
	const SceGxmBlendInfo *blend_info, SceGxmMultisampleMode msaa)
{
	int err;
	(void)err;

	err = sceGxmShaderPatcherCreateFragmentProgram(
		shaderPatcher,
		colorFragmentProgramId,
		SCE_GXM_OUTPUT_REGISTER_FORMAT_UCHAR4,
		msaa,
		blend_info,
		colorVertexProgramGxp,
		&out->color);

	VITA2D_DEBUG("color sceGxmShaderPatcherCreateFragmentProgram(): 0x%08X\n", err);

	err = sceGxmShaderPatcherCreateFragmentProgram(
		shaderPatcher,
		textureFragmentProgramId,
		SCE_GXM_OUTPUT_REGISTER_FORMAT_UCHAR4,
		msaa,
		blend_info,
		textureVertexProgramGxp,
		&out->texture);

	VITA2D_DEBUG("texture sceGxmShaderPatcherCreateFragmentProgram(): 0x%08X\n", err);

	err = sceGxmShaderPatcherCreateFragmentProgram(
		shaderPatcher,
		textureTintFragmentProgramId,
		SCE_GXM_OUTPUT_REGISTER_FORMAT_UCHAR4,
		msaa,
		blend_info,
		textureVertexProgramGxp,
		&out->textureTint);

	VITA2D_DEBUG("texture_tint sceGxmShaderPatcherCreateFragmentProgram(): 0x%08X\n", err);
}