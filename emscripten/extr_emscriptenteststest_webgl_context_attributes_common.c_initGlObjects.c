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
 int /*<<< orphan*/  GL_ARRAY_BUFFER ; 
 int /*<<< orphan*/  GL_STATIC_DRAW ; 
 int /*<<< orphan*/  createShaderProgram (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fragmentShaderSrc ; 
 int /*<<< orphan*/  glBindBuffer (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  glBufferData (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  glGenBuffers (int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  shaderProgram ; 
 int /*<<< orphan*/  vertexShaderSrc ; 
 int /*<<< orphan*/  vertices ; 
 int /*<<< orphan*/  vertices2 ; 
 int /*<<< orphan*/  verticesVBO ; 
 int /*<<< orphan*/  verticesVBO2 ; 

__attribute__((used)) static void initGlObjects() {
    glGenBuffers(1, &verticesVBO);
    glBindBuffer(GL_ARRAY_BUFFER, verticesVBO);
    glBufferData(GL_ARRAY_BUFFER, 9*sizeof(float), vertices, GL_STATIC_DRAW);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    
    glGenBuffers(1, &verticesVBO2);
    glBindBuffer(GL_ARRAY_BUFFER, verticesVBO2);
    glBufferData(GL_ARRAY_BUFFER, 9*sizeof(float), vertices2, GL_STATIC_DRAW);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    
    shaderProgram = createShaderProgram(vertexShaderSrc, fragmentShaderSrc);
}