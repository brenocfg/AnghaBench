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
typedef  int /*<<< orphan*/  rglgen_proc_address_t ;
typedef  int /*<<< orphan*/  fft_t ;

/* Variables and functions */
 int /*<<< orphan*/  GL_EXTENSIONS ; 
 int /*<<< orphan*/  GL_VERSION ; 
 scalar_t__ calloc (int,int) ; 
 int /*<<< orphan*/  fft_context_reset (int /*<<< orphan*/ *,unsigned int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ *) ; 
 scalar_t__ glGetString (int /*<<< orphan*/ ) ; 
 int sscanf (char const*,char*,unsigned int*,unsigned int*) ; 
 int /*<<< orphan*/  strstr (char const*,char*) ; 

fft_t *fft_new(unsigned fft_steps, rglgen_proc_address_t proc)
{
   fft_t *fft    = NULL;
#ifdef HAVE_OPENGLES3
   const char *ver = (const char*)(glGetString(GL_VERSION));
   if (ver)
   {
      unsigned major, minor;
      if (sscanf(ver, "OpenGL ES %u.%u", &major, &minor) != 2 || major < 3)
         return NULL;
   }
   else
      return NULL;
#else
   const char *exts = (const char*)(glGetString(GL_EXTENSIONS));
   if (!exts || !strstr(exts, "ARB_ES3_compatibility"))
      return NULL;
#endif
   fft = (fft_t*)calloc(1, sizeof(*fft));

   if (!fft)
      return NULL;

   if (!fft_context_reset(fft, fft_steps, proc, 256))
      goto error;

   return fft;

error:
   if (fft)
      free(fft);
   return NULL;
}