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
typedef  int /*<<< orphan*/  GLuint ;

/* Variables and functions */
 int /*<<< orphan*/  GL_FRAGMENT_SHADER ; 
 int /*<<< orphan*/  GL_VERTEX_SHADER ; 
 int /*<<< orphan*/  load_shader (int /*<<< orphan*/ ,char const*) ; 
 int /*<<< orphan*/  make_program (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

GLuint load_program(const char *path1, const char *path2) {
    GLuint shader1 = load_shader(GL_VERTEX_SHADER, path1);
    GLuint shader2 = load_shader(GL_FRAGMENT_SHADER, path2);
    GLuint program = make_program(shader1, shader2);
    return program;
}