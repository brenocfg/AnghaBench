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
struct TYPE_3__ {scalar_t__ ms_rb_ds; scalar_t__ ms_rb_color; scalar_t__ ms_fbo; } ;
typedef  TYPE_1__ fft_t ;

/* Variables and functions */
 int /*<<< orphan*/  GL_COLOR_ATTACHMENT0 ; 
 int /*<<< orphan*/  GL_DEPTH24_STENCIL8 ; 
 int /*<<< orphan*/  GL_DEPTH_STENCIL_ATTACHMENT ; 
 int /*<<< orphan*/  GL_FRAMEBUFFER ; 
 scalar_t__ GL_FRAMEBUFFER_COMPLETE ; 
 int /*<<< orphan*/  GL_RENDERBUFFER ; 
 int /*<<< orphan*/  GL_RGBA8 ; 
 int /*<<< orphan*/  glBindFramebuffer (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  glBindRenderbuffer (int /*<<< orphan*/ ,scalar_t__) ; 
 scalar_t__ glCheckFramebufferStatus (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  glDeleteFramebuffers (int,scalar_t__*) ; 
 int /*<<< orphan*/  glDeleteRenderbuffers (int,scalar_t__*) ; 
 int /*<<< orphan*/  glFramebufferRenderbuffer (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  glGenFramebuffers (int,scalar_t__*) ; 
 int /*<<< orphan*/  glGenRenderbuffers (int,scalar_t__*) ; 
 int /*<<< orphan*/  glRenderbufferStorageMultisample (int /*<<< orphan*/ ,unsigned int,int /*<<< orphan*/ ,unsigned int,unsigned int) ; 

void fft_init_multisample(fft_t *fft, unsigned width, unsigned height, unsigned samples)
{
   if (fft->ms_rb_color)
      glDeleteRenderbuffers(1, &fft->ms_rb_color);
   fft->ms_rb_color = 0;
   if (fft->ms_rb_ds)
      glDeleteRenderbuffers(1, &fft->ms_rb_ds);
   fft->ms_rb_ds    = 0;
   if (fft->ms_fbo)
      glDeleteFramebuffers(1, &fft->ms_fbo);
   fft->ms_fbo      = 0;

   if (samples > 1)
   {
      glGenRenderbuffers(1, &fft->ms_rb_color);
      glGenRenderbuffers(1, &fft->ms_rb_ds);
      glGenFramebuffers (1, &fft->ms_fbo);

      glBindRenderbuffer(GL_RENDERBUFFER, fft->ms_rb_color);
      glRenderbufferStorageMultisample(GL_RENDERBUFFER, samples,
            GL_RGBA8, width, height);
      glBindRenderbuffer(GL_RENDERBUFFER, fft->ms_rb_ds);
      glRenderbufferStorageMultisample(GL_RENDERBUFFER, samples,
            GL_DEPTH24_STENCIL8, width, height);
      glBindRenderbuffer(GL_RENDERBUFFER, 0);

      glBindFramebuffer(GL_FRAMEBUFFER, fft->ms_fbo);
      glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0,
            GL_RENDERBUFFER, fft->ms_rb_color);
      glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT,
            GL_RENDERBUFFER, fft->ms_rb_ds);
      if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
         fft_init_multisample(fft, 0, 0, 0);
   }

   glBindFramebuffer(GL_FRAMEBUFFER, 0);
}