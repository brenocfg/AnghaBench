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
typedef  int /*<<< orphan*/  GLfloat ;

/* Variables and functions */
 int /*<<< orphan*/  BUFFER_OFFSET (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GL_ARRAY_BUFFER ; 
 int /*<<< orphan*/  GL_FALSE ; 
 int /*<<< orphan*/  GL_FLOAT ; 
 int /*<<< orphan*/  GL_TRIANGLES ; 
 int WINDOWS_SIZE ; 
 int /*<<< orphan*/  glBindBuffer (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  glDrawArrays (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  glEnableVertexAttribArray (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  glGetAttribLocation (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  glGetUniformLocation (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  glUniform4f (int /*<<< orphan*/ ,unsigned char,unsigned char,unsigned char,unsigned char) ; 
 int /*<<< orphan*/  glUniformMatrix4fv (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  glUseProgram (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  glVertexAttribPointer (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ortho (int,int,int,int,int,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  shaderProgram ; 

__attribute__((used)) static void drawTriangle(GLuint verticesVBO, unsigned char r, unsigned char g, unsigned char b, unsigned char a) {
    glUseProgram(shaderProgram);
    GLuint posLoc = glGetAttribLocation(shaderProgram, "a_position");
    GLuint mvpLoc = glGetUniformLocation(shaderProgram, "u_mvpMatrix");
    GLuint colorLoc = glGetUniformLocation(shaderProgram, "u_color");
    
    GLfloat mvpMat[16];
    ortho(-WINDOWS_SIZE/2, WINDOWS_SIZE/2, -WINDOWS_SIZE/2, WINDOWS_SIZE/2, -100, 100, mvpMat);
    
    glUniformMatrix4fv(mvpLoc, 1, GL_FALSE, mvpMat);
    glUniform4f(colorLoc, r/255.f, g/255.f, b/255.f, a/255.f);
    
    glBindBuffer(GL_ARRAY_BUFFER, verticesVBO);  
    glEnableVertexAttribArray(posLoc);
    glVertexAttribPointer(posLoc, 3, GL_FLOAT, GL_FALSE, 3*sizeof(float), BUFFER_OFFSET(0));
    
    glDrawArrays(GL_TRIANGLES, 0, 3);
    
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glUseProgram(0);
}