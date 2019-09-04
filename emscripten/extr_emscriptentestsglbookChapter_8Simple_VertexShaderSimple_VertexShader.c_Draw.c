#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/ ** m; } ;
struct TYPE_6__ {int /*<<< orphan*/  numIndices; TYPE_1__ mvpMatrix; int /*<<< orphan*/  mvpLoc; int /*<<< orphan*/  indicesObject; int /*<<< orphan*/  positionLoc; int /*<<< orphan*/  vertPosObject; int /*<<< orphan*/  programObject; } ;
typedef  TYPE_2__ UserData ;
struct TYPE_7__ {int /*<<< orphan*/  height; int /*<<< orphan*/  width; TYPE_2__* userData; } ;
typedef  int /*<<< orphan*/  GLfloat ;
typedef  TYPE_3__ ESContext ;

/* Variables and functions */
 int /*<<< orphan*/  GL_ARRAY_BUFFER ; 
 int /*<<< orphan*/  GL_COLOR_BUFFER_BIT ; 
 int /*<<< orphan*/  GL_ELEMENT_ARRAY_BUFFER ; 
 int /*<<< orphan*/  GL_FALSE ; 
 int /*<<< orphan*/  GL_FLOAT ; 
 int /*<<< orphan*/  GL_TRIANGLES ; 
 int /*<<< orphan*/  GL_UNSIGNED_SHORT ; 
 int /*<<< orphan*/  glBindBuffer (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  glClear (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  glDrawElements (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  glEnableVertexAttribArray (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  glUniformMatrix4fv (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
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

   // Use the program object
   glUseProgram ( userData->programObject );

   // Load the vertex position
   glBindBuffer(GL_ARRAY_BUFFER, userData->vertPosObject);
   glVertexAttribPointer ( userData->positionLoc, 3, GL_FLOAT, 
                           GL_FALSE, 0, 0 );
   glEnableVertexAttribArray ( userData->positionLoc );
   
   
   // Load the index buffer
   glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, userData->indicesObject);

   // Load the MVP matrix
   glUniformMatrix4fv( userData->mvpLoc, 1, GL_FALSE, (GLfloat*) &userData->mvpMatrix.m[0][0] );
   
   // Draw the cube
   glDrawElements ( GL_TRIANGLES, userData->numIndices, GL_UNSIGNED_SHORT, 0 );
}