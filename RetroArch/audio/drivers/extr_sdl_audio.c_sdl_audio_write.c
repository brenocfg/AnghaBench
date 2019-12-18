#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  size_t ssize_t ;
struct TYPE_2__ {int /*<<< orphan*/  buffer; int /*<<< orphan*/  lock; int /*<<< orphan*/  cond; scalar_t__ nonblock; } ;
typedef  TYPE_1__ sdl_audio_t ;

/* Variables and functions */
 int /*<<< orphan*/  SDL_LockAudio () ; 
 int /*<<< orphan*/  SDL_UnlockAudio () ; 
 int /*<<< orphan*/  fifo_write (int /*<<< orphan*/ ,char const*,size_t) ; 
 size_t fifo_write_avail (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  scond_wait (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  slock_lock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  slock_unlock (int /*<<< orphan*/ ) ; 

__attribute__((used)) static ssize_t sdl_audio_write(void *data, const void *buf, size_t size)
{
   ssize_t ret      = 0;
   sdl_audio_t *sdl = (sdl_audio_t*)data;

   if (sdl->nonblock)
   {
      size_t avail, write_amt;

      SDL_LockAudio();
      avail = fifo_write_avail(sdl->buffer);
      write_amt = avail > size ? size : avail;
      fifo_write(sdl->buffer, buf, write_amt);
      SDL_UnlockAudio();
      ret = write_amt;
   }
   else
   {
      size_t written = 0;

      while (written < size)
      {
         size_t avail;

         SDL_LockAudio();
         avail = fifo_write_avail(sdl->buffer);

         if (avail == 0)
         {
            SDL_UnlockAudio();
#ifdef HAVE_THREADS
            slock_lock(sdl->lock);
            scond_wait(sdl->cond, sdl->lock);
            slock_unlock(sdl->lock);
#endif
         }
         else
         {
            size_t write_amt = size - written > avail ? avail : size - written;
            fifo_write(sdl->buffer, (const char*)buf + written, write_amt);
            SDL_UnlockAudio();
            written += write_amt;
         }
      }
      ret = written;
   }

   return ret;
}