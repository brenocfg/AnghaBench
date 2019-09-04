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
struct TYPE_4__ {int numIndices; int /*<<< orphan*/  indices; int /*<<< orphan*/  indicesObject; int /*<<< orphan*/  normals; int /*<<< orphan*/  vertNormalObject; int /*<<< orphan*/  vertices; int /*<<< orphan*/  vertPosObject; int /*<<< orphan*/  textureId; int /*<<< orphan*/  programObject; int /*<<< orphan*/  samplerLoc; void* normalLoc; void* positionLoc; } ;
typedef  TYPE_1__ UserData ;
struct TYPE_5__ {TYPE_1__* userData; } ;
typedef  char GLbyte ;
typedef  TYPE_2__ ESContext ;

/* Variables and functions */
 int /*<<< orphan*/  CreateSimpleTextureCubemap () ; 
 int /*<<< orphan*/  GL_ARRAY_BUFFER ; 
 int /*<<< orphan*/  GL_ELEMENT_ARRAY_BUFFER ; 
 int /*<<< orphan*/  GL_STATIC_DRAW ; 
 int GL_TRUE ; 
 int esGenSphere (int,float,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  esLoadProgram (char*,char*) ; 
 int /*<<< orphan*/  glBindBuffer (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  glBufferData (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  glClearColor (float,float,float,float) ; 
 int /*<<< orphan*/  glGenBuffers (int,int /*<<< orphan*/ *) ; 
 void* glGetAttribLocation (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  glGetUniformLocation (int /*<<< orphan*/ ,char*) ; 

int Init ( ESContext *esContext )
{
   //esContext->userData = malloc(sizeof(UserData));
   UserData *userData = esContext->userData;
   GLbyte vShaderStr[] =  
      "attribute vec4 a_position;   \n"
      "attribute vec3 a_normal;     \n"
      "varying vec3 v_normal;       \n"
      "void main()                  \n"
      "{                            \n"
      "   gl_Position = a_position; \n"
      "   v_normal = a_normal;      \n"
      "}                            \n";
   
   GLbyte fShaderStr[] =  
      "precision mediump float;                            \n"
      "varying vec3 v_normal;                              \n"
      "uniform samplerCube s_texture;                      \n"
      "void main()                                         \n"
      "{                                                   \n"
      "  gl_FragColor = textureCube( s_texture, v_normal );\n"
      "}                                                   \n";

   // Load the shaders and get a linked program object
   userData->programObject = esLoadProgram ( vShaderStr, fShaderStr );

   // Get the attribute locations
   userData->positionLoc = glGetAttribLocation ( userData->programObject, "a_position" );
   userData->normalLoc = glGetAttribLocation ( userData->programObject, "a_normal" );
   
   // Get the sampler locations
   userData->samplerLoc = glGetUniformLocation ( userData->programObject, "s_texture" );

   // Load the texture
   userData->textureId = CreateSimpleTextureCubemap ();

   // Generate the vertex data
   userData->numIndices = esGenSphere ( 20, 0.75f, &userData->vertices, &userData->normals,
                                        NULL, &userData->indices );

   // Generate the VBOs
   glGenBuffers(1, &userData->vertPosObject);
   glBindBuffer(GL_ARRAY_BUFFER, userData->vertPosObject);
   glBufferData(GL_ARRAY_BUFFER, 21 * 21 * 4 * 3, userData->vertices, GL_STATIC_DRAW );

   glGenBuffers(1, &userData->vertNormalObject);
   glBindBuffer(GL_ARRAY_BUFFER, userData->vertNormalObject );
   glBufferData(GL_ARRAY_BUFFER, 21 * 21 * 4 * 3, userData->normals, GL_STATIC_DRAW );

   glGenBuffers(1, &userData->indicesObject);
   glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, userData->indicesObject );
   glBufferData(GL_ELEMENT_ARRAY_BUFFER, 2 * userData->numIndices, userData->indices, GL_STATIC_DRAW );

   glClearColor ( 0.0f, 0.0f, 0.0f, 1.0f );
   return GL_TRUE;
}