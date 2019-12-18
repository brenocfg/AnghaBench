#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  quad_buffer ;
struct TYPE_3__ {int /*<<< orphan*/  quad; int /*<<< orphan*/  vao; } ;
typedef  TYPE_1__ fft_t ;
typedef  int /*<<< orphan*/  GLvoid ;
typedef  int GLbyte ;

/* Variables and functions */
 int /*<<< orphan*/  GL_ARRAY_BUFFER ; 
 int /*<<< orphan*/  GL_BYTE ; 
 int /*<<< orphan*/  GL_FALSE ; 
 int /*<<< orphan*/  GL_STATIC_DRAW ; 
 int /*<<< orphan*/  glBindBuffer (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  glBindVertexArray (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  glBufferData (int /*<<< orphan*/ ,int,int const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  glEnableVertexAttribArray (int) ; 
 int /*<<< orphan*/  glGenBuffers (int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  glGenVertexArrays (int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  glVertexAttribPointer (int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/  const*) ; 

__attribute__((used)) static void fft_init_quad_vao(fft_t *fft)
{
   static const GLbyte quad_buffer[] = {
      -1, -1, 1, -1, -1, 1, 1, 1,
       0,  0, 1,  0,  0, 1, 1, 1,
   };
   glGenBuffers(1, &fft->quad);
   glBindBuffer(GL_ARRAY_BUFFER, fft->quad);
   glBufferData(GL_ARRAY_BUFFER,
         sizeof(quad_buffer), quad_buffer, GL_STATIC_DRAW);
   glBindBuffer(GL_ARRAY_BUFFER, 0);

   glGenVertexArrays(1, &fft->vao);
   glBindVertexArray(fft->vao);
   glBindBuffer(GL_ARRAY_BUFFER, fft->quad);
   glEnableVertexAttribArray(0);
   glEnableVertexAttribArray(1);
   glVertexAttribPointer(0, 2, GL_BYTE, GL_FALSE, 0, 0);
   glVertexAttribPointer(1, 2, GL_BYTE, GL_FALSE, 0,
         (const GLvoid*)((uintptr_t)(8)));
   glBindVertexArray(0);
   glBindBuffer(GL_ARRAY_BUFFER, 0);
}