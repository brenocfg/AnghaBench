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
 int /*<<< orphan*/  _vita2d_context ; 
 int /*<<< orphan*/  _vita2d_textureTintFragmentProgram ; 
 int /*<<< orphan*/  _vita2d_textureVertexProgram ; 
 int /*<<< orphan*/  sceGxmSetFragmentProgram (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sceGxmSetVertexProgram (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline void set_texture_tint_program()
{
	sceGxmSetVertexProgram(_vita2d_context, _vita2d_textureVertexProgram);
	sceGxmSetFragmentProgram(_vita2d_context, _vita2d_textureTintFragmentProgram);
}