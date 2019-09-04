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
struct TYPE_5__ {int /*<<< orphan*/  textureId; int /*<<< orphan*/  programObject; void* offsetLoc; void* samplerLoc; void* texCoordLoc; void* positionLoc; } ;
typedef  TYPE_1__ UserData ;
struct TYPE_6__ {TYPE_1__* userData; } ;
typedef  char GLbyte ;
typedef  TYPE_2__ ESContext ;

/* Variables and functions */
 int /*<<< orphan*/  CreateMipMappedTexture2D () ; 
 int GL_TRUE ; 
 int /*<<< orphan*/  esLoadProgram (char*,char*) ; 
 int /*<<< orphan*/  glClearColor (float,float,float,float) ; 
 void* glGetAttribLocation (int /*<<< orphan*/ ,char*) ; 
 void* glGetUniformLocation (int /*<<< orphan*/ ,char*) ; 
 TYPE_1__* malloc (int) ; 

int Init ( ESContext *esContext )
{
   esContext->userData = malloc(sizeof(UserData));
	
   UserData *userData = esContext->userData;
   GLbyte vShaderStr[] =
      "uniform float u_offset;      \n"
      "attribute vec4 a_position;   \n"
      "attribute vec2 a_texCoord;   \n"
      "varying vec2 v_texCoord;     \n"
      "void main()                  \n"
      "{                            \n"
      "   gl_Position = a_position; \n"
      "   gl_Position.x += u_offset;\n"
      "   v_texCoord = a_texCoord;  \n"
      "}                            \n";
   
   GLbyte fShaderStr[] =  
      "precision mediump float;                            \n"
      "varying vec2 v_texCoord;                            \n"
      "uniform sampler2D s_texture;                        \n"
      "void main()                                         \n"
      "{                                                   \n"
      "  gl_FragColor = texture2D( s_texture, v_texCoord );\n"
      "}                                                   \n";

   // Load the shaders and get a linked program object
   userData->programObject = esLoadProgram ( vShaderStr, fShaderStr );

   // Get the attribute locations
   userData->positionLoc = glGetAttribLocation ( userData->programObject, "a_position" );
   userData->texCoordLoc = glGetAttribLocation ( userData->programObject, "a_texCoord" );
   
   // Get the sampler location
   userData->samplerLoc = glGetUniformLocation ( userData->programObject, "s_texture" );

   // Get the offset location
   userData->offsetLoc = glGetUniformLocation( userData->programObject, "u_offset" );

   // Load the texture
   userData->textureId = CreateMipMappedTexture2D ();

   glClearColor ( 0.0f, 0.0f, 0.0f, 0.0f );
   return GL_TRUE;
}