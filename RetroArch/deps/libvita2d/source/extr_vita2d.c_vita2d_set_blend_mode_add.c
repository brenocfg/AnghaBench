#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  textureTint; int /*<<< orphan*/  texture; int /*<<< orphan*/  color; } ;
typedef  TYPE_1__ vita2d_fragment_programs ;
struct TYPE_4__ {TYPE_1__ blend_mode_normal; TYPE_1__ blend_mode_add; } ;

/* Variables and functions */
 int /*<<< orphan*/  _vita2d_colorFragmentProgram ; 
 TYPE_2__ _vita2d_fragmentPrograms ; 
 int /*<<< orphan*/  _vita2d_textureFragmentProgram ; 
 int /*<<< orphan*/  _vita2d_textureTintFragmentProgram ; 

void vita2d_set_blend_mode_add(int enable)
{
	vita2d_fragment_programs *in = enable ? &_vita2d_fragmentPrograms.blend_mode_add
	    : &_vita2d_fragmentPrograms.blend_mode_normal;

	_vita2d_colorFragmentProgram = in->color;
	_vita2d_textureFragmentProgram = in->texture;
	_vita2d_textureTintFragmentProgram = in->textureTint;
}