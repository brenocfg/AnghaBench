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
struct TYPE_3__ {int /*<<< orphan*/  cond; int /*<<< orphan*/  lock; int /*<<< orphan*/  buffer; } ;
typedef  TYPE_1__ sdl_audio_t ;

/* Variables and functions */
 int /*<<< orphan*/  SDL_CloseAudio () ; 
 int /*<<< orphan*/  SDL_INIT_AUDIO ; 
 int /*<<< orphan*/  SDL_QuitSubSystem (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fifo_free (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free (TYPE_1__*) ; 
 int /*<<< orphan*/  scond_free (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  slock_free (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void sdl_audio_free(void *data)
{
   sdl_audio_t *sdl = (sdl_audio_t*)data;

   SDL_CloseAudio();
   SDL_QuitSubSystem(SDL_INIT_AUDIO);

   if (sdl)
   {
      fifo_free(sdl->buffer);
#ifdef HAVE_THREADS
      slock_free(sdl->lock);
      scond_free(sdl->cond);
#endif
   }
   free(sdl);
}