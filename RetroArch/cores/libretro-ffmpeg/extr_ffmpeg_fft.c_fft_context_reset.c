#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct Pass {int dummy; } ;
typedef  int /*<<< orphan*/  rglgen_proc_address_t ;
struct TYPE_6__ {unsigned int steps; unsigned int depth; int size; int block_size; unsigned int passes_size; int sliding_size; int /*<<< orphan*/ * sliding; struct Pass* passes; } ;
typedef  TYPE_1__ fft_t ;
typedef  int /*<<< orphan*/  GLshort ;

/* Variables and functions */
 int /*<<< orphan*/  GL_CHECK_ERROR () ; 
 scalar_t__ calloc (unsigned int,int) ; 
 int /*<<< orphan*/  fft_init (TYPE_1__*) ; 
 int /*<<< orphan*/  fft_init_block (TYPE_1__*) ; 
 int /*<<< orphan*/  fft_init_quad_vao (TYPE_1__*) ; 
 int /*<<< orphan*/  rglgen_resolve_symbols (int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool fft_context_reset(fft_t *fft, unsigned fft_steps,
      rglgen_proc_address_t proc, unsigned fft_depth)
{
   rglgen_resolve_symbols(proc);

   fft->steps       = fft_steps;
   fft->depth       = fft_depth;
   fft->size        = 1 << fft_steps;
   fft->block_size  = fft->size / 4 + 1;

   fft->passes_size = fft_steps;
   fft->passes      = (struct Pass*)calloc(fft->passes_size, sizeof(struct Pass));

   if (!fft->passes)
      return false;

   fft->sliding_size = 2 * fft->size;
   fft->sliding      = (GLshort*)calloc(fft->sliding_size, sizeof(GLshort));

   if (!fft->sliding)
      return false;

   GL_CHECK_ERROR();
   fft_init_quad_vao(fft);
   GL_CHECK_ERROR();
   fft_init(fft);
   GL_CHECK_ERROR();
   fft_init_block(fft);
   GL_CHECK_ERROR();

   return true;
}