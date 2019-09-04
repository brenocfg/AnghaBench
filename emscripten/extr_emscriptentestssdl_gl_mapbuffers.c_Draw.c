#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  vVertices ;
typedef  int /*<<< orphan*/  GLuint ;
typedef  float GLfloat ;

/* Variables and functions */
 int /*<<< orphan*/  GL_ARRAY_BUFFER ; 
 int /*<<< orphan*/  GL_COLOR_BUFFER_BIT ; 
 int /*<<< orphan*/  GL_FLOAT ; 
 int GL_MAP_FLUSH_EXPLICIT_BIT ; 
 int GL_MAP_INVALIDATE_BUFFER_BIT ; 
 int GL_MAP_WRITE_BIT ; 
 int /*<<< orphan*/  GL_STATIC_DRAW ; 
 int /*<<< orphan*/  GL_TRIANGLES ; 
 int /*<<< orphan*/  exit (int) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  glBindBuffer (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  glBufferData (int /*<<< orphan*/ ,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  glClear (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  glDrawArrays (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  glEnableVertexAttribArray (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  glFlushMappedBufferRange (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  glGenBuffers (int,int /*<<< orphan*/ *) ; 
 int glGetError () ; 
 void* glMapBufferRange (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  glUnmapBuffer (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  glUseProgram (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  glVertexAttribPointer (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  glViewport (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  height ; 
 int /*<<< orphan*/  memcpy (void*,float*,int) ; 
 int /*<<< orphan*/  programObject ; 
 int /*<<< orphan*/  stderr ; 
 int /*<<< orphan*/  width ; 

void Draw ()
{
   void *buffer;
   GLfloat vVertices[] = {  0.0f,  0.5f, 0.0f, 
                           -0.5f, -0.5f, 0.0f,
                            0.5f, -0.5f, 0.0f };

   // No clientside arrays, so do this in a webgl-friendly manner
   GLuint vertexPosObject;
   glGenBuffers(1, &vertexPosObject);
   glBindBuffer(GL_ARRAY_BUFFER, vertexPosObject);
   glBufferData(GL_ARRAY_BUFFER, sizeof(vVertices), NULL, GL_STATIC_DRAW);
   buffer = glMapBufferRange(
     GL_ARRAY_BUFFER,
     0,
     sizeof(vVertices),
     GL_MAP_FLUSH_EXPLICIT_BIT | GL_MAP_INVALIDATE_BUFFER_BIT | GL_MAP_WRITE_BIT
   );
   if (buffer == NULL) {
     fprintf(stderr, "Could not map buffer: %x\n", glGetError());
     exit(1);
   }
   memcpy(buffer, vVertices, sizeof(vVertices));
   glFlushMappedBufferRange(GL_ARRAY_BUFFER, 0, sizeof(vVertices));
   glUnmapBuffer(GL_ARRAY_BUFFER);
   
   glViewport ( 0, 0, width, height );
   glClear ( GL_COLOR_BUFFER_BIT );
   glUseProgram ( programObject );

   glBindBuffer(GL_ARRAY_BUFFER, vertexPosObject);
   glVertexAttribPointer(0 /* ? */, 3, GL_FLOAT, 0, 0, 0);
   glEnableVertexAttribArray(0);

   glDrawArrays ( GL_TRIANGLES, 0, 3 );
}