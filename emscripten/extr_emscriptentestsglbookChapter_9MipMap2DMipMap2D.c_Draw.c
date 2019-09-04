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
struct TYPE_4__ {int /*<<< orphan*/  offsetLoc; int /*<<< orphan*/  samplerLoc; int /*<<< orphan*/  textureId; int /*<<< orphan*/  texCoordLoc; int /*<<< orphan*/  positionLoc; int /*<<< orphan*/  programObject; } ;
typedef  TYPE_1__ UserData ;
struct TYPE_5__ {int /*<<< orphan*/  height; int /*<<< orphan*/  width; TYPE_1__* userData; } ;
typedef  int GLushort ;
typedef  float GLfloat ;
typedef  TYPE_2__ ESContext ;

/* Variables and functions */
 int /*<<< orphan*/  GL_COLOR_BUFFER_BIT ; 
 int /*<<< orphan*/  GL_FALSE ; 
 int /*<<< orphan*/  GL_FLOAT ; 
 int /*<<< orphan*/  GL_LINEAR_MIPMAP_LINEAR ; 
 int /*<<< orphan*/  GL_NEAREST ; 
 int /*<<< orphan*/  GL_TEXTURE0 ; 
 int /*<<< orphan*/  GL_TEXTURE_2D ; 
 int /*<<< orphan*/  GL_TEXTURE_MIN_FILTER ; 
 int /*<<< orphan*/  GL_TRIANGLES ; 
 int /*<<< orphan*/  GL_UNSIGNED_SHORT ; 
 int /*<<< orphan*/  glActiveTexture (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  glBindTexture (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  glClear (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  glDrawElements (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  glEnableVertexAttribArray (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  glTexParameteri (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  glUniform1f (int /*<<< orphan*/ ,float) ; 
 int /*<<< orphan*/  glUniform1i (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  glUseProgram (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  glVertexAttribPointer (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,float*) ; 
 int /*<<< orphan*/  glViewport (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void Draw ( ESContext *esContext )
{
   UserData *userData = esContext->userData;
   GLfloat vVertices[] = { -0.5f,  0.5f, 0.0f, 1.5f,  // Position 0
                            0.0f,  0.0f,              // TexCoord 0 
                           -0.5f, -0.5f, 0.0f, 0.75f, // Position 1
                            0.0f,  1.0f,              // TexCoord 1
                            0.5f, -0.5f, 0.0f, 0.75f, // Position 2
                            1.0f,  1.0f,              // TexCoord 2
                            0.5f,  0.5f, 0.0f, 1.5f,  // Position 3
                            1.0f,  0.0f               // TexCoord 3
                         };
   GLushort indices[] = { 0, 1, 2, 0, 2, 3 };
      
   // Set the viewport
   glViewport ( 0, 0, esContext->width, esContext->height );
   
   // Clear the color buffer
   glClear ( GL_COLOR_BUFFER_BIT );

   // Use the program object
   glUseProgram ( userData->programObject );

   // Load the vertex position
   glVertexAttribPointer ( userData->positionLoc, 4, GL_FLOAT, 
                           GL_FALSE, 6 * sizeof(GLfloat), vVertices );
   // Load the texture coordinate
   glVertexAttribPointer ( userData->texCoordLoc, 2, GL_FLOAT,
                           GL_FALSE, 6 * sizeof(GLfloat), &vVertices[4] );

   glEnableVertexAttribArray ( userData->positionLoc );
   glEnableVertexAttribArray ( userData->texCoordLoc );

   // Bind the texture
   glActiveTexture ( GL_TEXTURE0 );
   glBindTexture ( GL_TEXTURE_2D, userData->textureId );

   // Set the sampler texture unit to 0
   glUniform1i ( userData->samplerLoc, 0 );

   // Draw quad with nearest sampling
   glTexParameteri ( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST );
   glUniform1f ( userData->offsetLoc, -0.6f );   
   glDrawElements ( GL_TRIANGLES, 6, GL_UNSIGNED_SHORT, indices );

   // Draw quad with trilinear filtering
   glTexParameteri ( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR );
   glUniform1f ( userData->offsetLoc, 0.6f );
   glDrawElements ( GL_TRIANGLES, 6, GL_UNSIGNED_SHORT, indices );

}