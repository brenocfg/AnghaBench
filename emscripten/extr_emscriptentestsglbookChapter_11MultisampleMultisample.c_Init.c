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
struct TYPE_4__ {int /*<<< orphan*/  programObject; int /*<<< orphan*/  colorLoc; int /*<<< orphan*/  positionLoc; } ;
typedef  TYPE_1__ UserData ;
struct TYPE_5__ {TYPE_1__* userData; } ;
typedef  char GLbyte ;
typedef  TYPE_2__ ESContext ;

/* Variables and functions */
 int /*<<< orphan*/  GL_DEPTH_TEST ; 
 int /*<<< orphan*/  GL_STENCIL_TEST ; 
 int TRUE ; 
 int /*<<< orphan*/  esLoadProgram (char*,char*) ; 
 int /*<<< orphan*/  glClearColor (float,float,float,float) ; 
 int /*<<< orphan*/  glClearDepthf (float) ; 
 int /*<<< orphan*/  glClearStencil (int) ; 
 int /*<<< orphan*/  glEnable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  glGetAttribLocation (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  glGetUniformLocation (int /*<<< orphan*/ ,char*) ; 

int Init ( ESContext *esContext )
{
   UserData *userData = esContext->userData;
   GLbyte vShaderStr[] =  
      "attribute vec4 a_position;   \n"
      "void main()                  \n"
      "{                            \n"
      "   gl_Position = a_position; \n"
      "}                            \n";
   
   GLbyte fShaderStr[] =  
      "precision mediump float;  \n"
      "uniform vec4  u_color;    \n"
      "void main()               \n"
      "{                         \n"
      "  gl_FragColor = u_color; \n"
      "}                         \n";

   // Load the shaders and get a linked program object
   userData->programObject = esLoadProgram ( vShaderStr, fShaderStr );

   // Get the attribute locations
   userData->positionLoc = glGetAttribLocation ( userData->programObject, "a_position" );
   
   // Get the sampler location
   userData->colorLoc = glGetUniformLocation ( userData->programObject, "u_color" );

   // Set the clear color
   glClearColor ( 0.0f, 0.0f, 0.0f, 0.0f );
   
   // Set the stencil clear value
   glClearStencil ( 0x1 );

   // Set the depth clear value
   glClearDepthf( 0.75f );

   // Enable the depth and stencil tests
   glEnable( GL_DEPTH_TEST );
   glEnable( GL_STENCIL_TEST );

   return TRUE;
}