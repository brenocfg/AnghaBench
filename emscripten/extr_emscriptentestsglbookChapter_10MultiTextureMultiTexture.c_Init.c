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
struct TYPE_4__ {scalar_t__ baseMapTexId; scalar_t__ lightMapTexId; int /*<<< orphan*/  indexObject; int /*<<< orphan*/  vertexObject; int /*<<< orphan*/  programObject; void* lightMapLoc; void* baseMapLoc; void* texCoordLoc; void* positionLoc; } ;
typedef  TYPE_1__ UserData ;
struct TYPE_5__ {TYPE_1__* userData; } ;
typedef  int GLushort ;
typedef  double GLfloat ;
typedef  char GLbyte ;
typedef  TYPE_2__ ESContext ;

/* Variables and functions */
 int FALSE ; 
 int /*<<< orphan*/  GL_ARRAY_BUFFER ; 
 int /*<<< orphan*/  GL_ELEMENT_ARRAY_BUFFER ; 
 int /*<<< orphan*/  GL_STATIC_DRAW ; 
 void* LoadTexture (char*) ; 
 int TRUE ; 
 int /*<<< orphan*/  esLoadProgram (char*,char*) ; 
 int /*<<< orphan*/  glBindBuffer (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  glBufferData (int /*<<< orphan*/ ,int,...) ; 
 int /*<<< orphan*/  glClearColor (double,double,double,double) ; 
 int /*<<< orphan*/  glGenBuffers (int,int /*<<< orphan*/ *) ; 
 void* glGetAttribLocation (int /*<<< orphan*/ ,char*) ; 
 void* glGetUniformLocation (int /*<<< orphan*/ ,char*) ; 

int Init ( ESContext *esContext )
{
   UserData *userData = esContext->userData;
   GLbyte vShaderStr[] =  
      "attribute vec4 a_position;   \n"
      "attribute vec2 a_texCoord;   \n"
      "varying vec2 v_texCoord;     \n"
      "void main()                  \n"
      "{                            \n"
      "   gl_Position = a_position; \n"
      "   v_texCoord = a_texCoord;  \n"
      "}                            \n";
   
   GLbyte fShaderStr[] =  
      "precision mediump float;                            \n"
      "varying vec2 v_texCoord;                            \n"
      "uniform sampler2D s_baseMap;                        \n"
      "uniform sampler2D s_lightMap;                       \n"
      "void main()                                         \n"
      "{                                                   \n"
      "  vec4 baseColor;                                   \n"
      "  vec4 lightColor;                                  \n"
      "                                                    \n"
      "  baseColor = texture2D( s_baseMap, v_texCoord );   \n"
      "  lightColor = texture2D( s_lightMap, v_texCoord ); \n"
      "  gl_FragColor = baseColor * (lightColor + 0.25);   \n"
      "}                                                   \n";

   // Load the shaders and get a linked program object
   userData->programObject = esLoadProgram ( vShaderStr, fShaderStr );

   // Get the attribute locations
   userData->positionLoc = glGetAttribLocation ( userData->programObject, "a_position" );
   userData->texCoordLoc = glGetAttribLocation ( userData->programObject, "a_texCoord" );
   
   // Get the sampler location
   userData->baseMapLoc = glGetUniformLocation ( userData->programObject, "s_baseMap" );
   userData->lightMapLoc = glGetUniformLocation ( userData->programObject, "s_lightMap" );

   // Load the textures
   userData->baseMapTexId = LoadTexture ( "basemap.tga" );
   userData->lightMapTexId = LoadTexture ( "lightmap.tga" );

   if ( userData->baseMapTexId == 0 || userData->lightMapTexId == 0 )
      return FALSE;

   GLfloat vVertices[] = { -0.5,  0.5, 0.0,  // Position 0
                            0.0,  0.0,       // TexCoord 0
                           -0.5, -0.5, 0.0,  // Position 1
                            0.0,  1.0,       // TexCoord 1
                            0.5, -0.5, 0.0,  // Position 2
                            1.0,  1.0,       // TexCoord 2
                            0.5,  0.5, 0.0,  // Position 3
                            1.0,  0.0        // TexCoord 3
                         };
   GLushort indices[] = { 0, 1, 2, 0, 2, 3 };

   glGenBuffers(1, &userData->vertexObject);
   glBindBuffer ( GL_ARRAY_BUFFER, userData->vertexObject );
   glBufferData ( GL_ARRAY_BUFFER, 5 * 4 * 4, vVertices, GL_STATIC_DRAW );

   glGenBuffers(1, &userData->indexObject);
   glBindBuffer ( GL_ELEMENT_ARRAY_BUFFER, userData->indexObject );
   glBufferData ( GL_ELEMENT_ARRAY_BUFFER, 6 * 2, indices, GL_STATIC_DRAW );

   glClearColor ( 0.0, 0.0, 0.0, 1.0 );

   return TRUE;
}