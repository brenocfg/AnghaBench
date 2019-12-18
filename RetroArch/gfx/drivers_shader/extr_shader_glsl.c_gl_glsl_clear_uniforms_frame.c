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
struct shader_uniforms_frame {int texture; int texture_size; int input_size; int tex_coord; } ;

/* Variables and functions */

__attribute__((used)) static void gl_glsl_clear_uniforms_frame(struct shader_uniforms_frame *frame)
{
   frame->texture      = -1;
   frame->texture_size = -1;
   frame->input_size   = -1;
   frame->tex_coord    = -1;
}