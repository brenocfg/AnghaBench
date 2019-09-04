#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  lightMapLoc; int /*<<< orphan*/  lightMapTexId; int /*<<< orphan*/  baseMapLoc; int /*<<< orphan*/  baseMapTexId; int /*<<< orphan*/  texCoordLoc; int /*<<< orphan*/  positionLoc; int /*<<< orphan*/  programObject; } ;
typedef  TYPE_1__ UserData ;
struct TYPE_5__ {int /*<<< orphan*/  eglSurface; int /*<<< orphan*/  eglDisplay; int /*<<< orphan*/  height; int /*<<< orphan*/  width; TYPE_1__* userData; } ;
typedef  int GLushort ;
typedef  float GLfloat ;
typedef  TYPE_2__ ESContext ;

/* Variables and functions */
 int /*<<< orphan*/  GL_COLOR_BUFFER_BIT ; 
 int /*<<< orphan*/  GL_FALSE ; 
 int /*<<< orphan*/  GL_FLOAT ; 
 int /*<<< orphan*/  GL_TEXTURE0 ; 
 int /*<<< orphan*/  GL_TEXTURE1 ; 
 int /*<<< orphan*/  GL_TEXTURE_2D ; 
 int /*<<< orphan*/  GL_TRIANGLES ; 
 int /*<<< orphan*/  GL_UNSIGNED_SHORT ; 
 int /*<<< orphan*/  eglSwapBuffers (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  glActiveTexture (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  glBindTexture (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  glClear (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  glDrawElements (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  glEnableVertexAttribArray (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  glUniform1i (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  glUseProgram (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  glVertexAttribPointer (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,float*) ; 
 int /*<<< orphan*/  glViewport (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void Draw ( ESContext *esContext )
{
   UserData *userData = esContext->userData;
   GLfloat vVertices[] = { -0.5f,  0.5f, 0.0f,  // Position 0
                            0.0f,  0.0f,        // TexCoord 0 
                           -0.5f, -0.5f, 0.0f,  // Position 1
                            0.0f,  1.0f,        // TexCoord 1
                            0.5f, -0.5f, 0.0f,  // Position 2
                            1.0f,  1.0f,        // TexCoord 2
                            0.5f,  0.5f, 0.0f,  // Position 3
                            1.0f,  0.0f         // TexCoord 3
                         };
   GLushort indices[] = { 0, 1, 2, 0, 2, 3 };
      
   // Set the viewport
   glViewport ( 0, 0, esContext->width, esContext->height );
   
   // Clear the color buffer
   glClear ( GL_COLOR_BUFFER_BIT );

   // Use the program object
   glUseProgram ( userData->programObject );

   // Load the vertex position
   glVertexAttribPointer ( userData->positionLoc, 3, GL_FLOAT, 
                           GL_FALSE, 5 * sizeof(GLfloat), vVertices );
   // Load the texture coordinate
   glVertexAttribPointer ( userData->texCoordLoc, 2, GL_FLOAT,
                           GL_FALSE, 5 * sizeof(GLfloat), &vVertices[3] );

   glEnableVertexAttribArray ( userData->positionLoc );
   glEnableVertexAttribArray ( userData->texCoordLoc );

   // Bind the base map
   glActiveTexture ( GL_TEXTURE0 );
   glBindTexture ( GL_TEXTURE_2D, userData->baseMapTexId );

   // Set the base map sampler to texture unit to 0
   glUniform1i ( userData->baseMapLoc, 0 );

   // Bind the light map
   glActiveTexture ( GL_TEXTURE1 );
   glBindTexture ( GL_TEXTURE_2D, userData->lightMapTexId );
   
   // Set the light map sampler to texture unit 1
   glUniform1i ( userData->lightMapLoc, 1 );

   glDrawElements ( GL_TRIANGLES, 6, GL_UNSIGNED_SHORT, indices );

   eglSwapBuffers ( esContext->eglDisplay, esContext->eglSurface );
}