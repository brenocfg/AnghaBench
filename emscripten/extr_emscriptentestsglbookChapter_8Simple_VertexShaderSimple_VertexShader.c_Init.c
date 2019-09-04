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
struct TYPE_5__ {int numIndices; float angle; int /*<<< orphan*/  indices; int /*<<< orphan*/  indicesObject; int /*<<< orphan*/  vertices; int /*<<< orphan*/  vertPosObject; int /*<<< orphan*/  programObject; int /*<<< orphan*/  mvpLoc; int /*<<< orphan*/  positionLoc; } ;
typedef  TYPE_1__ UserData ;
struct TYPE_6__ {TYPE_1__* userData; } ;
typedef  int /*<<< orphan*/  GLushort ;
typedef  int /*<<< orphan*/  GLfloat ;
typedef  char GLbyte ;
typedef  TYPE_2__ ESContext ;

/* Variables and functions */
 int /*<<< orphan*/  GL_ARRAY_BUFFER ; 
 int /*<<< orphan*/  GL_ELEMENT_ARRAY_BUFFER ; 
 int /*<<< orphan*/  GL_STATIC_DRAW ; 
 int GL_TRUE ; 
 int esGenCube (double,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  esLoadProgram (char*,char*) ; 
 int /*<<< orphan*/  glBindBuffer (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  glBufferData (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  glClearColor (float,float,float,float) ; 
 int /*<<< orphan*/  glGenBuffers (int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  glGetAttribLocation (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  glGetUniformLocation (int /*<<< orphan*/ ,char*) ; 
 TYPE_1__* malloc (int) ; 

int Init ( ESContext *esContext )
{
   esContext->userData = malloc(sizeof(UserData));
	
   UserData *userData = esContext->userData;
   GLbyte vShaderStr[] =  
      "uniform mat4 u_mvpMatrix;                   \n"
      "attribute vec4 a_position;                  \n"
      "void main()                                 \n"
      "{                                           \n"
      "   gl_Position = u_mvpMatrix * a_position;  \n"
      "}                                           \n";
   
   GLbyte fShaderStr[] =  
      "precision mediump float;                            \n"
      "void main()                                         \n"
      "{                                                   \n"
      "  gl_FragColor = vec4( 1.0, 0.0, 0.0, 1.0 );        \n"
      "}                                                   \n";

   // Load the shaders and get a linked program object
   userData->programObject = esLoadProgram ( vShaderStr, fShaderStr );

   // Get the attribute locations
   userData->positionLoc = glGetAttribLocation ( userData->programObject, "a_position" );

   // Get the uniform locations
   userData->mvpLoc = glGetUniformLocation( userData->programObject, "u_mvpMatrix" );
   
   // Generate the vertex data
   userData->numIndices = esGenCube( 1.0, &userData->vertices,
                                     NULL, NULL, &userData->indices );
   
   // Starting rotation angle for the cube
   userData->angle = 45.0f;

   glGenBuffers(1, &userData->vertPosObject);
   glBindBuffer(GL_ARRAY_BUFFER, userData->vertPosObject);
   glBufferData(GL_ARRAY_BUFFER, 24 * sizeof(GLfloat) * 3, userData->vertices, GL_STATIC_DRAW);

   glGenBuffers(1, &userData->indicesObject);
   glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, userData->indicesObject);
   glBufferData(GL_ELEMENT_ARRAY_BUFFER, userData->numIndices * sizeof(GLushort), userData->indices, GL_STATIC_DRAW);

   glClearColor ( 0.0f, 0.0f, 0.0f, 0.0f );
   return GL_TRUE;
}