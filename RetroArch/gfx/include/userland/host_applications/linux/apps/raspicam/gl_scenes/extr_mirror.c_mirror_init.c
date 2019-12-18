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
typedef  int /*<<< orphan*/  RASPITEX_STATE ;

/* Variables and functions */
 int /*<<< orphan*/  mirror_shader ; 
 int raspitexutil_build_shader_program (int /*<<< orphan*/ *) ; 
 int raspitexutil_gl_init_2_0 (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int mirror_init(RASPITEX_STATE *state)
{
    int rc = raspitexutil_gl_init_2_0(state);
    if (rc != 0)
       goto end;

    rc = raspitexutil_build_shader_program(&mirror_shader);
end:
    return rc;
}