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
struct TYPE_5__ {int /*<<< orphan*/  indexObject; int /*<<< orphan*/  vertexObject; int /*<<< orphan*/  textureId; int /*<<< orphan*/  programObject; void* offsetLoc; void* samplerLoc; void* texCoordLoc; void* positionLoc; } ;
typedef  TYPE_1__ UserData ;
struct TYPE_6__ {TYPE_1__* userData; } ;
typedef  int GLushort ;
typedef  double GLfloat ;
typedef  char GLbyte ;
typedef  TYPE_2__ ESContext ;

/* Variables and functions */
 int /*<<< orphan*/  CreateTexture2D () ; 
 int /*<<< orphan*/  GL_ARRAY_BUFFER ; 
 int /*<<< orphan*/  GL_ELEMENT_ARRAY_BUFFER ; 
 int /*<<< orphan*/  GL_STATIC_DRAW ; 
 int GL_TRUE ; 
 int /*<<< orphan*/  esLoadProgram (char*,char*) ; 
 int /*<<< orphan*/  glBindBuffer (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  glBufferData (int /*<<< orphan*/ ,int,...) ; 
 int /*<<< orphan*/  glClearColor (double,double,double,double) ; 
 int /*<<< orphan*/  glGenBuffers (int,int /*<<< orphan*/ *) ; 
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
   userData->textureId = CreateTexture2D ();

   // Setup the vertex data
   GLfloat vVertices[] = { -0.3,  0.3, 0.0, 1.0,  // Position 0
                           -1.0,  -1.0,           // TexCoord 0
                           -0.3, -0.3, 0.0, 1.0,  // Position 1
                           -1.0,  2.0,            // TexCoord 1
                            0.3, -0.3, 0.0, 1.0,  // Position 2
                            2.0,  2.0,            // TexCoord 2
                            0.3,  0.3, 0.0, 1.0,  // Position 3
                            2.0,  -1.0            // TexCoord 3
                         };
   GLushort indices[] = { 0, 1, 2, 0, 2, 3 };

   glGenBuffers(1, &userData->vertexObject);
   glBindBuffer ( GL_ARRAY_BUFFER, userData->vertexObject );
   glBufferData ( GL_ARRAY_BUFFER, 6 * 4 * 4, vVertices, GL_STATIC_DRAW );

   glGenBuffers(1, &userData->indexObject);
   glBindBuffer ( GL_ELEMENT_ARRAY_BUFFER, userData->indexObject );
   glBufferData ( GL_ELEMENT_ARRAY_BUFFER, 6 * 2, indices, GL_STATIC_DRAW );

   glClearColor ( 0.0, 0.0, 0.0, 1.0 );

   return GL_TRUE;
}