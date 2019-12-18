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

/* Variables and functions */
 int /*<<< orphan*/  sceGxmShaderPatcherReleaseFragmentProgram (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  shaderPatcher ; 

__attribute__((used)) static void _vita2d_free_fragment_programs(vita2d_fragment_programs *out)
{
	sceGxmShaderPatcherReleaseFragmentProgram(shaderPatcher, out->color);
	sceGxmShaderPatcherReleaseFragmentProgram(shaderPatcher, out->texture);
	sceGxmShaderPatcherReleaseFragmentProgram(shaderPatcher, out->textureTint);
}