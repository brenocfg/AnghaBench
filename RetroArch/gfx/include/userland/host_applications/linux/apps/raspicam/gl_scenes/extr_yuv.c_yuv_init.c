#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int /*<<< orphan*/ * uniform_locations; int /*<<< orphan*/  program; } ;
struct TYPE_6__ {int /*<<< orphan*/  egl_config_attribs; } ;
typedef  TYPE_1__ RASPITEX_STATE ;

/* Variables and functions */
 int /*<<< orphan*/  GLCHK (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  glUniform1i (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  glUseProgram (int /*<<< orphan*/ ) ; 
 int raspitexutil_build_shader_program (TYPE_2__*) ; 
 int raspitexutil_gl_init_2_0 (TYPE_1__*) ; 
 int /*<<< orphan*/  yuv_egl_config_attribs ; 
 TYPE_2__ yuv_shader ; 

__attribute__((used)) static int yuv_init(RASPITEX_STATE *state)
{
    int rc;
    state->egl_config_attribs = yuv_egl_config_attribs;
    rc = raspitexutil_gl_init_2_0(state);
    if (rc != 0)
       goto end;

    rc = raspitexutil_build_shader_program(&yuv_shader);
    GLCHK(glUseProgram(yuv_shader.program));
    GLCHK(glUniform1i(yuv_shader.uniform_locations[0], 0)); // tex unit
end:
    return rc;
}