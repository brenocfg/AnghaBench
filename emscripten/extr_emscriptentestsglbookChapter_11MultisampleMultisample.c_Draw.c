#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/  colorLoc; int /*<<< orphan*/  positionLoc; int /*<<< orphan*/  programObject; } ;
typedef  TYPE_1__ UserData ;
struct TYPE_8__ {int /*<<< orphan*/  height; int /*<<< orphan*/  width; TYPE_1__* userData; } ;
struct TYPE_7__ {int member_0; int member_1; int member_2; int member_3; int member_4; int member_5; } ;
typedef  int GLuint ;
typedef  TYPE_2__ GLubyte ;
typedef  int GLint ;
typedef  float GLfloat ;
typedef  TYPE_3__ ESContext ;

/* Variables and functions */
 int GL_COLOR_BUFFER_BIT ; 
 int /*<<< orphan*/  GL_DECR ; 
 int GL_DEPTH_BUFFER_BIT ; 
 int /*<<< orphan*/  GL_EQUAL ; 
 int /*<<< orphan*/  GL_FALSE ; 
 int /*<<< orphan*/  GL_FLOAT ; 
 int /*<<< orphan*/  GL_GREATER ; 
 int /*<<< orphan*/  GL_INCR ; 
 int /*<<< orphan*/  GL_INVERT ; 
 int /*<<< orphan*/  GL_KEEP ; 
 int /*<<< orphan*/  GL_LESS ; 
 int /*<<< orphan*/  GL_REPLACE ; 
 int /*<<< orphan*/  GL_STENCIL_BITS ; 
 int GL_STENCIL_BUFFER_BIT ; 
 int /*<<< orphan*/  GL_TRIANGLES ; 
 int /*<<< orphan*/  GL_UNSIGNED_BYTE ; 
 int /*<<< orphan*/  glClear (int) ; 
 int /*<<< orphan*/  glDrawElements (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,TYPE_2__*) ; 
 int /*<<< orphan*/  glEnableVertexAttribArray (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  glGetIntegerv (int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  glStencilFunc (int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  glStencilMask (int) ; 
 int /*<<< orphan*/  glStencilOp (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  glUniform4fv (int /*<<< orphan*/ ,int,float*) ; 
 int /*<<< orphan*/  glUseProgram (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  glVertexAttribPointer (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,float*) ; 
 int /*<<< orphan*/  glViewport (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void Draw ( ESContext *esContext )
{
   int  i;

   UserData *userData = esContext->userData;

   GLfloat vVertices[] = { 
       -0.75f,  0.25f,  0.50f, // Quad #0
       -0.25f,  0.25f,  0.50f,
       -0.25f,  0.75f,  0.50f,
       -0.75f,  0.75f,  0.50f,
	    0.25f,  0.25f,  0.90f, // Quad #1
		0.75f,  0.25f,  0.90f,
		0.75f,  0.75f,  0.90f,
		0.25f,  0.75f,  0.90f,
	   -0.75f, -0.75f,  0.50f, // Quad #2
       -0.25f, -0.75f,  0.50f,
       -0.25f, -0.25f,  0.50f,
       -0.75f, -0.25f,  0.50f,
        0.25f, -0.75f,  0.50f, // Quad #3
        0.75f, -0.75f,  0.50f,
        0.75f, -0.25f,  0.50f,
        0.25f, -0.25f,  0.50f,
       -1.00f, -1.00f,  0.00f, // Big Quad
        1.00f, -1.00f,  0.00f,
        1.00f,  1.00f,  0.00f,
       -1.00f,  1.00f,  0.00f
   };

   GLubyte indices[][6] = { 
       {  0,  1,  2,  0,  2,  3 }, // Quad #0
       {  4,  5,  6,  4,  6,  7 }, // Quad #1
       {  8,  9, 10,  8, 10, 11 }, // Quad #2
       { 12, 13, 14, 12, 14, 15 }, // Quad #3
       { 16, 17, 18, 16, 18, 19 }  // Big Quad
   };
   
#define NumTests  4
   GLfloat  colors[NumTests][4] = { 
       { 1.0f, 0.0f, 0.0f, 1.0f },
       { 0.0f, 1.0f, 0.0f, 1.0f },
       { 0.0f, 0.0f, 1.0f, 1.0f },
       { 1.0f, 1.0f, 0.0f, 0.0f }
   };

   GLint   numStencilBits;
   GLuint  stencilValues[NumTests] = { 
      0x7, // Result of test 0
      0x0, // Result of test 1
      0x2, // Result of test 2
      0xff // Result of test 3.  We need to fill this
           //  value in a run-time
   };

   // Set the viewport
   glViewport ( 0, 0, esContext->width, esContext->height );
   
   // Clear the color, depth, and stencil buffers.  At this
   //   point, the stencil buffer will be 0x1 for all pixels
   glClear ( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT );

   // Use the program object
   glUseProgram ( userData->programObject );

   // Load the vertex position
   glVertexAttribPointer ( userData->positionLoc, 3, GL_FLOAT, 
                           GL_FALSE, 0, vVertices );
  
   glEnableVertexAttribArray ( userData->positionLoc );

   // Test 0:
   //
   // Initialize upper-left region.  In this case, the
   //   stencil-buffer values will be replaced because the
   //   stencil test for the rendered pixels will fail the
   //   stencil test, which is
   //
   //        ref   mask   stencil  mask
   //      ( 0x7 & 0x3 ) < ( 0x1 & 0x7 )
   //
   //   The value in the stencil buffer for these pixels will
   //   be 0x7.
   //
   glStencilFunc( GL_LESS, 0x7, 0x3 );
   glStencilOp( GL_REPLACE, GL_DECR, GL_DECR );
   glDrawElements( GL_TRIANGLES, 6, GL_UNSIGNED_BYTE, indices[0] );
 
   // Test 1:
   //
   // Initialize the upper-right region.  Here, we'll decrement
   //   the stencil-buffer values where the stencil test passes
   //   but the depth test fails.  The stencil test is
   //
   //        ref  mask    stencil  mask
   //      ( 0x3 & 0x3 ) > ( 0x1 & 0x3 )
   //
   //    but where the geometry fails the depth test.  The
   //    stencil values for these pixels will be 0x0.
   //
   glStencilFunc( GL_GREATER, 0x3, 0x3 );
   glStencilOp( GL_KEEP, GL_DECR, GL_KEEP );
   glDrawElements( GL_TRIANGLES, 6, GL_UNSIGNED_BYTE, indices[1] );

   // Test 2:
   //
   // Initialize the lower-left region.  Here we'll increment 
   //   (with saturation) the stencil value where both the
   //   stencil and depth tests pass.  The stencil test for
   //   these pixels will be
   //
   //        ref  mask     stencil  mask
   //      ( 0x1 & 0x3 ) == ( 0x1 & 0x3 )
   //
   //   The stencil values for these pixels will be 0x2.
   //
   glStencilFunc( GL_EQUAL, 0x1, 0x3 );
   glStencilOp( GL_KEEP, GL_INCR, GL_INCR );
   glDrawElements( GL_TRIANGLES, 6, GL_UNSIGNED_BYTE, indices[2] );

   // Test 3:
   //
   // Finally, initialize the lower-right region.  We'll invert
   //   the stencil value where the stencil tests fails.  The
   //   stencil test for these pixels will be
   //
   //        ref   mask    stencil  mask
   //      ( 0x2 & 0x1 ) == ( 0x1 & 0x1 )
   //
   //   The stencil value here will be set to ~((2^s-1) & 0x1),
   //   (with the 0x1 being from the stencil clear value),
   //   where 's' is the number of bits in the stencil buffer
   //
   glStencilFunc( GL_EQUAL, 0x2, 0x1 );
   glStencilOp( GL_INVERT, GL_KEEP, GL_KEEP );
   glDrawElements( GL_TRIANGLES, 6, GL_UNSIGNED_BYTE, indices[3] );
   
   // Since we don't know at compile time how many stecil bits are present,
   //   we'll query, and update the value correct value in the
   //   stencilValues arrays for the fourth tests.  We'll use this value
   //   later in rendering.
   glGetIntegerv( GL_STENCIL_BITS, &numStencilBits );
   
   stencilValues[3] = ~(((1 << numStencilBits) - 1) & 0x1) & 0xff;

   // Use the stencil buffer for controlling where rendering will
   //   occur.  We diable writing to the stencil buffer so we
   //   can test against them without modifying the values we
   //   generated.
   glStencilMask( 0x0 );
   
   for ( i = 0; i < NumTests; ++i )
   {
      glStencilFunc( GL_EQUAL, stencilValues[i], 0xff );
      glUniform4fv( userData->colorLoc, 1, colors[i] );
      glDrawElements( GL_TRIANGLES, 6, GL_UNSIGNED_BYTE, indices[4] );
   }

   //eglSwapBuffers ( esContext->eglDisplay, esContext->eglSurface );
}