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
typedef  int /*<<< orphan*/  uint32_t ;
typedef  size_t ssize_t ;
struct TYPE_2__ {scalar_t__ write_ptr; size_t dma_write; size_t dma_next; size_t dma_busy; scalar_t__* data; int /*<<< orphan*/  nonblock; } ;
typedef  TYPE_1__ gx_audio_t ;

/* Variables and functions */
 int BLOCKS ; 
 scalar_t__ CHUNK_FRAMES ; 
 int /*<<< orphan*/  copy_swapped (scalar_t__,int /*<<< orphan*/  const*,size_t) ; 

__attribute__((used)) static ssize_t gx_audio_write(void *data, const void *buf_, size_t size)
{
   size_t       frames = size >> 2;
   const uint32_t *buf = buf_;
   gx_audio_t      *wa = data;

   while (frames)
   {
      size_t to_write = CHUNK_FRAMES - wa->write_ptr;

      if (frames < to_write)
         to_write = frames;

      /* FIXME: Nonblocking audio should break out of loop
       * when it has nothing to write. */
      while ((wa->dma_write == wa->dma_next ||
               wa->dma_write == wa->dma_busy) && !wa->nonblock);

      copy_swapped(wa->data[wa->dma_write] + wa->write_ptr, buf, to_write);

      wa->write_ptr += to_write;
      frames -= to_write;
      buf += to_write;

      if (wa->write_ptr >= CHUNK_FRAMES)
      {
         wa->write_ptr -= CHUNK_FRAMES;
         wa->dma_write = (wa->dma_write + 1) & (BLOCKS - 1);
      }
   }

   return size;
}