#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int ssize_t ;
struct TYPE_4__ {size_t current_pool_ptr; size_t mempool; int buffer_size; size_t current_size; int /*<<< orphan*/ * current_wavebuf; int /*<<< orphan*/  drv; int /*<<< orphan*/  update_lock; int /*<<< orphan*/ * wavebufs; } ;
typedef  TYPE_1__ libnx_audren_t ;

/* Variables and functions */
 int /*<<< orphan*/  armDCacheFlush (void*,size_t) ; 
 int /*<<< orphan*/  audrvUpdate (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  audrvVoiceAddWaveBuf (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  audrvVoiceIsPlaying (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  audrvVoiceStart (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int libnx_audren_audio_get_free_wavebuf_idx (TYPE_1__*) ; 
 int /*<<< orphan*/  memcpy (void*,void const*,size_t) ; 
 int /*<<< orphan*/  mutexLock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutexUnlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static size_t libnx_audren_audio_append(libnx_audren_t* aud, const void *buf, size_t size)
{
   ssize_t free_idx = -1;

   if(!aud->current_wavebuf)
   {
      free_idx = libnx_audren_audio_get_free_wavebuf_idx(aud);
      if(free_idx == -1)
         return 0;

      aud->current_wavebuf = &aud->wavebufs[free_idx];
      aud->current_pool_ptr = aud->mempool + (free_idx * aud->buffer_size);
      aud->current_size = 0;
   }

   if(size > aud->buffer_size - aud->current_size)
   {
      size = aud->buffer_size - aud->current_size;
   }

   void *dstbuf = aud->current_pool_ptr + aud->current_size;
   memcpy(dstbuf, buf, size);
   armDCacheFlush(dstbuf, size);

   aud->current_size += size;

   if(aud->current_size == aud->buffer_size)
   {
      audrvVoiceAddWaveBuf(&aud->drv, 0, aud->current_wavebuf);

      mutexLock(&aud->update_lock);
      audrvUpdate(&aud->drv);
      mutexUnlock(&aud->update_lock);

      if (!audrvVoiceIsPlaying(&aud->drv, 0))
      {
         audrvVoiceStart(&aud->drv, 0);
      }

      aud->current_wavebuf = NULL;
   }

   return size;
}