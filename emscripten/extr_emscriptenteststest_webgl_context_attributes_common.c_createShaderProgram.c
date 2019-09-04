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
 int /*<<< orphan*/  createShader (char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  glAttachShader (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  glCreateProgram () ; 
 int /*<<< orphan*/  glLinkProgram (int /*<<< orphan*/ ) ; 

__attribute__((used)) static GLuint createShaderProgram(const char *vertexShaderSrc, const char *fragmentShaderSrc) {
    GLuint program = glCreateProgram();
    glAttachShader(program, createShader(vertexShaderSrc, GL_VERTEX_SHADER));
    glAttachShader(program, createShader(fragmentShaderSrc, GL_FRAGMENT_SHADER));
    glLinkProgram(program);
    return program;
}