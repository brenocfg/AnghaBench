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
struct TYPE_5__ {int elems; int /*<<< orphan*/  ibo; int /*<<< orphan*/  vao; int /*<<< orphan*/  vbo; int /*<<< orphan*/  prog; } ;
struct TYPE_6__ {int block_size; int depth; TYPE_1__ block; } ;
typedef  TYPE_2__ fft_t ;
typedef  unsigned int GLushort ;
typedef  unsigned int GLuint ;

/* Variables and functions */
 int /*<<< orphan*/  GL_ARRAY_BUFFER ; 
 int /*<<< orphan*/  GL_ELEMENT_ARRAY_BUFFER ; 
 int /*<<< orphan*/  GL_FALSE ; 
 int /*<<< orphan*/  GL_STATIC_DRAW ; 
 int /*<<< orphan*/  GL_UNSIGNED_SHORT ; 
 scalar_t__ calloc (unsigned int,int) ; 
 int /*<<< orphan*/  fft_compile_program (TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fft_fragment_program_heightmap ; 
 int /*<<< orphan*/  fft_vertex_program_heightmap ; 
 int /*<<< orphan*/  free (unsigned int*) ; 
 int /*<<< orphan*/  glBindBuffer (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  glBindVertexArray (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  glBufferData (int /*<<< orphan*/ ,unsigned int,unsigned int*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  glEnableVertexAttribArray (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  glGenBuffers (int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  glGenVertexArrays (int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  glGetUniformLocation (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  glUniform1i (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  glUseProgram (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  glVertexAttribPointer (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void fft_init_block(fft_t *fft)
{
   unsigned x, y;
   unsigned block_vertices_size = 0;
   unsigned block_indices_size  = 0;
   int pos                      = 0;
   GLuint *bp                   = NULL;
   GLushort *block_vertices     = NULL;
   GLuint   *block_indices      = NULL;

   fft->block.prog              = fft_compile_program(fft,
         fft_vertex_program_heightmap, fft_fragment_program_heightmap);

   glUseProgram(fft->block.prog);
   glUniform1i(glGetUniformLocation(fft->block.prog, "sHeight"), 0);

   block_vertices_size = 2 * fft->block_size * fft->depth;
   block_vertices      = (GLushort*)calloc(block_vertices_size, sizeof(GLushort));

   for (y = 0; y < fft->depth; y++)
   {
      for (x = 0; x < fft->block_size; x++)
      {
         block_vertices[2 * (y * fft->block_size + x) + 0] = x;
         block_vertices[2 * (y * fft->block_size + x) + 1] = y;
      }
   }
   glGenBuffers(1, &fft->block.vbo);
   glBindBuffer(GL_ARRAY_BUFFER, fft->block.vbo);
   glBufferData(GL_ARRAY_BUFFER,
         block_vertices_size * sizeof(GLushort),
         &block_vertices[0], GL_STATIC_DRAW);

   fft->block.elems = (2 * fft->block_size - 1) * (fft->depth - 1) + 1;

   block_indices_size = fft->block.elems;
   block_indices = (GLuint*)calloc(block_indices_size, sizeof(GLuint));

   bp = &block_indices[0];

   for (y = 0; y < fft->depth - 1; y++)
   {
      int x;
      int step_odd  = (-(int)(fft->block_size)) + ((y & 1) ? -1 : 1);
      int step_even = fft->block_size;

      for (x = 0; x < 2 * (int)(fft->block_size) - 1; x++)
      {
         *bp++ = pos;
         pos += (x & 1) ? step_odd : step_even;
      }
   }
   *bp++ = pos;

   glGenVertexArrays(1, &fft->block.vao);
   glBindVertexArray(fft->block.vao);

   glGenBuffers(1, &fft->block.ibo);
   glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, fft->block.ibo);
   glBufferData(GL_ELEMENT_ARRAY_BUFFER,
         block_indices_size * sizeof(GLuint),
         &block_indices[0], GL_STATIC_DRAW);

   glEnableVertexAttribArray(0);
   glVertexAttribPointer(0, 2, GL_UNSIGNED_SHORT, GL_FALSE, 0, 0);
   glBindVertexArray(0);

   glBindBuffer(GL_ARRAY_BUFFER, 0);
   glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

   free(block_vertices);
   free(block_indices);
}