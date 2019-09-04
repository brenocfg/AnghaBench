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
struct TYPE_4__ {int /*<<< orphan*/  numIndices; int /*<<< orphan*/  indicesObject; int /*<<< orphan*/  samplerLoc; int /*<<< orphan*/  textureId; int /*<<< orphan*/  normalLoc; int /*<<< orphan*/  positionLoc; int /*<<< orphan*/  vertNormalObject; int /*<<< orphan*/  vertPosObject; int /*<<< orphan*/  programObject; } ;
typedef  TYPE_1__ UserData ;
struct TYPE_5__ {int /*<<< orphan*/  height; int /*<<< orphan*/  width; TYPE_1__* userData; } ;
typedef  TYPE_2__ ESContext ;

/* Variables and functions */
 int /*<<< orphan*/  GL_ARRAY_BUFFER ; 
 int /*<<< orphan*/  GL_BACK ; 
 int /*<<< orphan*/  GL_COLOR_BUFFER_BIT ; 
 int /*<<< orphan*/  GL_CULL_FACE ; 
 int /*<<< orphan*/  GL_ELEMENT_ARRAY_BUFFER ; 
 int /*<<< orphan*/  GL_FALSE ; 
 int /*<<< orphan*/  GL_FLOAT ; 
 int /*<<< orphan*/  GL_TEXTURE0 ; 
 int /*<<< orphan*/  GL_TEXTURE_CUBE_MAP ; 
 int /*<<< orphan*/  GL_TRIANGLES ; 
 int /*<<< orphan*/  GL_UNSIGNED_SHORT ; 
 int /*<<< orphan*/  glActiveTexture (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  glBindBuffer (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  glBindTexture (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  glClear (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  glCullFace (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  glDrawElements (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  glEnable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  glEnableVertexAttribArray (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  glUniform1i (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  glUseProgram (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  glVertexAttribPointer (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  glViewport (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void Draw ( ESContext *esContext )
{
   UserData *userData = esContext->userData;

   // Set the viewport
   glViewport ( 0, 0, esContext->width, esContext->height );
   
   // Clear the color buffer
   glClear ( GL_COLOR_BUFFER_BIT );

   glCullFace ( GL_BACK );
   glEnable ( GL_CULL_FACE );
   
   // Use the program object
   glUseProgram ( userData->programObject );

   // Load the vertex position
   glBindBuffer ( GL_ARRAY_BUFFER, userData->vertPosObject );
   glVertexAttribPointer ( userData->positionLoc, 3, GL_FLOAT,
                            GL_FALSE, 0, 0 );
   // Load the normal
   glBindBuffer ( GL_ARRAY_BUFFER, userData->vertNormalObject );
   glVertexAttribPointer ( userData->normalLoc, 3, GL_FLOAT,
                            GL_FALSE, 0, 0 );

   glEnableVertexAttribArray ( userData->positionLoc );
   glEnableVertexAttribArray ( userData->normalLoc );

   // Bind the texture
   glActiveTexture ( GL_TEXTURE0 );
   glBindTexture ( GL_TEXTURE_CUBE_MAP, userData->textureId );

   // Set the sampler texture unit to 0
   glUniform1i ( userData->samplerLoc, 0 );

   glBindBuffer ( GL_ELEMENT_ARRAY_BUFFER, userData->indicesObject );
   glDrawElements ( GL_TRIANGLES, userData->numIndices,
                     GL_UNSIGNED_SHORT, 0 );
}