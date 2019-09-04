#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  samplerLoc; int /*<<< orphan*/  textureId; int /*<<< orphan*/  startPositionLoc; int /*<<< orphan*/  endPositionLoc; int /*<<< orphan*/  lifetimeLoc; int /*<<< orphan*/  vertexObject; int /*<<< orphan*/  programObject; } ;
typedef  TYPE_1__ UserData ;
struct TYPE_6__ {int /*<<< orphan*/  eglSurface; int /*<<< orphan*/  eglDisplay; int /*<<< orphan*/  height; int /*<<< orphan*/  width; TYPE_1__* userData; } ;
typedef  int /*<<< orphan*/  GLfloat ;
typedef  TYPE_2__ ESContext ;

/* Variables and functions */
 int /*<<< orphan*/  GL_ARRAY_BUFFER ; 
 int /*<<< orphan*/  GL_BLEND ; 
 int /*<<< orphan*/  GL_COLOR_BUFFER_BIT ; 
 int /*<<< orphan*/  GL_FALSE ; 
 int /*<<< orphan*/  GL_FLOAT ; 
 int /*<<< orphan*/  GL_ONE ; 
 int /*<<< orphan*/  GL_POINTS ; 
 int /*<<< orphan*/  GL_SRC_ALPHA ; 
 int /*<<< orphan*/  GL_TEXTURE0 ; 
 int /*<<< orphan*/  GL_TEXTURE_2D ; 
 int /*<<< orphan*/  NUM_PARTICLES ; 
 int PARTICLE_SIZE ; 
 int /*<<< orphan*/  Update (TYPE_2__*,int) ; 
 int /*<<< orphan*/  eglSwapBuffers (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  glActiveTexture (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  glBindBuffer (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  glBindTexture (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  glBlendFunc (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  glClear (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  glDrawArrays (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  glEnable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  glEnableVertexAttribArray (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  glUniform1i (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  glUseProgram (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  glVertexAttribPointer (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  glViewport (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void Draw ( ESContext *esContext )
{
   UserData *userData = esContext->userData;
      
   // Set the viewport
   glViewport ( 0, 0, esContext->width, esContext->height );
   
   // Clear the color buffer
   glClear ( GL_COLOR_BUFFER_BIT );

   // Use the program object
   glUseProgram ( userData->programObject );

   // Load the vertex attributes
   glBindBuffer( GL_ARRAY_BUFFER, userData->vertexObject );
   glVertexAttribPointer ( userData->lifetimeLoc, 1, GL_FLOAT, 
                           GL_FALSE, PARTICLE_SIZE * sizeof(GLfloat), 
                           0 );
   
   glVertexAttribPointer ( userData->endPositionLoc, 3, GL_FLOAT,
                           GL_FALSE, PARTICLE_SIZE * sizeof(GLfloat),
                           4 );

   glVertexAttribPointer ( userData->startPositionLoc, 3, GL_FLOAT,
                           GL_FALSE, PARTICLE_SIZE * sizeof(GLfloat),
                           4 * 4 );

   
   glEnableVertexAttribArray ( userData->lifetimeLoc );
   glEnableVertexAttribArray ( userData->endPositionLoc );
   glEnableVertexAttribArray ( userData->startPositionLoc );
   // Blend particles
   glEnable ( GL_BLEND );
   glBlendFunc ( GL_SRC_ALPHA, GL_ONE );

   // Bind the texture
   glActiveTexture ( GL_TEXTURE0 );
   glBindTexture ( GL_TEXTURE_2D, userData->textureId );
   //glEnable ( GL_TEXTURE_2D );

   // Set the sampler texture unit to 0
   glUniform1i ( userData->samplerLoc, 0 );

   Update ( esContext, 133 * 0.001125 );

   glDrawArrays( GL_POINTS, 0, NUM_PARTICLES );
   
   eglSwapBuffers ( esContext->eglDisplay, esContext->eglSurface );
}