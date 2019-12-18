#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/  cond; int /*<<< orphan*/  lock; int /*<<< orphan*/  buffer; } ;
typedef  TYPE_2__ coreaudio_t ;
typedef  int /*<<< orphan*/  UInt32 ;
struct TYPE_7__ {int mNumberBuffers; TYPE_1__* mBuffers; } ;
struct TYPE_5__ {unsigned int mDataByteSize; void* mData; } ;
typedef  int /*<<< orphan*/  OSStatus ;
typedef  int /*<<< orphan*/  AudioUnitRenderActionFlags ;
typedef  int /*<<< orphan*/  AudioTimeStamp ;
typedef  TYPE_3__ AudioBufferList ;

/* Variables and functions */
 int /*<<< orphan*/  fifo_read (int /*<<< orphan*/ ,void*,unsigned int) ; 
 unsigned int fifo_read_avail (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kAudioUnitRenderAction_OutputIsSilence ; 
 int /*<<< orphan*/  memset (void*,int /*<<< orphan*/ ,unsigned int) ; 
 int /*<<< orphan*/  noErr ; 
 int /*<<< orphan*/  scond_signal (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  slock_lock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  slock_unlock (int /*<<< orphan*/ ) ; 

__attribute__((used)) static OSStatus audio_write_cb(void *userdata,
      AudioUnitRenderActionFlags *action_flags,
      const AudioTimeStamp *time_stamp, UInt32 bus_number,
      UInt32 number_frames, AudioBufferList *io_data)
{
   unsigned write_avail;
   void     *outbuf = NULL;
   coreaudio_t *dev = (coreaudio_t*)userdata;

   (void)time_stamp;
   (void)bus_number;
   (void)number_frames;

   if (!io_data || io_data->mNumberBuffers != 1)
      return noErr;

   write_avail = io_data->mBuffers[0].mDataByteSize;
   outbuf      = io_data->mBuffers[0].mData;

   slock_lock(dev->lock);

   if (fifo_read_avail(dev->buffer) < write_avail)
   {
      *action_flags = kAudioUnitRenderAction_OutputIsSilence;

      /* Seems to be needed. */
      memset(outbuf, 0, write_avail);

      slock_unlock(dev->lock);

      /* Technically possible to deadlock without. */
      scond_signal(dev->cond);
      return noErr;
   }

   fifo_read(dev->buffer, outbuf, write_avail);
   slock_unlock(dev->lock);
   scond_signal(dev->cond);
   return noErr;
}