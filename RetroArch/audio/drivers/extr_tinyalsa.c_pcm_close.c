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
struct pcm {int flags; int fd; scalar_t__ buffer_size; scalar_t__ running; scalar_t__ prepared; int /*<<< orphan*/  mmap_buffer; } ;

/* Variables and functions */
 int PCM_MMAP ; 
 struct pcm bad_pcm ; 
 int /*<<< orphan*/  close (int) ; 
 int /*<<< orphan*/  free (struct pcm*) ; 
 int /*<<< orphan*/  munmap (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pcm_frames_to_bytes (struct pcm*,scalar_t__) ; 
 int /*<<< orphan*/  pcm_hw_munmap_status (struct pcm*) ; 
 int /*<<< orphan*/  pcm_stop (struct pcm*) ; 

__attribute__((used)) static int pcm_close(struct pcm *pcm)
{
   if (pcm == &bad_pcm)
      return 0;

   pcm_hw_munmap_status(pcm);

   if (pcm->flags & PCM_MMAP)
   {
      pcm_stop(pcm);
      munmap(pcm->mmap_buffer, pcm_frames_to_bytes(pcm, pcm->buffer_size));
   }

   if (pcm->fd >= 0)
      close(pcm->fd);
   pcm->prepared = 0;
   pcm->running = 0;
   pcm->buffer_size = 0;
   pcm->fd = -1;
   free(pcm);
   return 0;
}