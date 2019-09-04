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
typedef  int /*<<< orphan*/  GLchar ;

/* Variables and functions */
 int /*<<< orphan*/  glCompileShader (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  glCreateShader (int) ; 
 int /*<<< orphan*/  glShaderSource (int /*<<< orphan*/ ,int,int /*<<< orphan*/  const**,int /*<<< orphan*/ *) ; 

__attribute__((used)) static GLuint createShader(const char *source, int type) {
    GLuint shader = glCreateShader(type);
    glShaderSource(shader, 1, (const GLchar**)(&source), NULL);
    glCompileShader(shader);
    return shader;
}