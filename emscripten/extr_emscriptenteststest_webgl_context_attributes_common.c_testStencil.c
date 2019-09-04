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
 int GL_COLOR_BUFFER_BIT ; 
 int /*<<< orphan*/  GL_KEEP ; 
 int /*<<< orphan*/  GL_LEQUAL ; 
 int /*<<< orphan*/  GL_REPLACE ; 
 int /*<<< orphan*/  GL_RGBA ; 
 int GL_STENCIL_BUFFER_BIT ; 
 int /*<<< orphan*/  GL_STENCIL_TEST ; 
 int /*<<< orphan*/  GL_UNSIGNED_BYTE ; 
 int WINDOWS_SIZE ; 
 float* backgroundColor ; 
 int /*<<< orphan*/  drawTriangle (int /*<<< orphan*/ ,unsigned char,unsigned char,unsigned char,unsigned char) ; 
 int /*<<< orphan*/  glClear (int) ; 
 int /*<<< orphan*/  glClearColor (float,float,float,float) ; 
 int /*<<< orphan*/  glClearStencil (int) ; 
 int /*<<< orphan*/  glDisable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  glEnable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  glReadPixels (int,int,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned char*) ; 
 int /*<<< orphan*/  glStencilFunc (int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  glStencilOp (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  glViewport (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int) ; 
 unsigned char* triangleColor ; 
 unsigned char* triangleColor2 ; 
 int /*<<< orphan*/  verticesVBO ; 

__attribute__((used)) static bool testStencil(bool activated) {
    glViewport(0, 0, WINDOWS_SIZE, WINDOWS_SIZE);
    glClearColor(backgroundColor[0]/255.f, backgroundColor[1]/255.f, backgroundColor[2]/255.f, backgroundColor[3]/255.f);
    glClearStencil(0xFF);
    glStencilOp(GL_KEEP,GL_KEEP,GL_REPLACE);
    glClear(GL_COLOR_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
    
    glEnable(GL_STENCIL_TEST);
    
    glStencilFunc(GL_LEQUAL, 0x1, 0xFF);
    drawTriangle(verticesVBO, triangleColor[0], triangleColor[1], triangleColor[2], triangleColor[3]);
    
    glStencilFunc(GL_LEQUAL, 0xFF, 0xFF);
    drawTriangle(verticesVBO, triangleColor2[0], triangleColor2[1], triangleColor2[2], triangleColor2[3]);
    
    glDisable(GL_STENCIL_TEST);
    
    unsigned char buffer[4];
    glReadPixels(WINDOWS_SIZE/2, WINDOWS_SIZE/2, 1, 1, GL_RGBA, GL_UNSIGNED_BYTE, &buffer[0]);
    
    bool firstTriangleColor = (buffer[0] == triangleColor[0] && buffer[1] == triangleColor[1] &&
                               buffer[2] == triangleColor[2] && buffer[3] == triangleColor[3]);
    
    bool secondTriangleColor = (buffer[0] == triangleColor2[0] && buffer[1] == triangleColor2[1] &&
                                buffer[2] == triangleColor2[2] && buffer[3] == triangleColor2[3]);
    
    return (activated && firstTriangleColor) || (!activated && secondTriangleColor);
}