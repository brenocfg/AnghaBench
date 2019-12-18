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
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int uint32_t ;
typedef  scalar_t__ int32_t ;
typedef  int /*<<< orphan*/  int16_t ;
typedef  int /*<<< orphan*/  AUDIOPLAY_STATE_T ;

/* Variables and functions */
 int BUFFER_SIZE_SAMPLES ; 
 int CTTW_SLEEP_TIME ; 
 int MIN_LATENCY_TIME ; 
 unsigned int OUT_CHANNELS (int) ; 
 int /*<<< orphan*/  SIN (int) ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/ * audio_dest ; 
 scalar_t__ audioplay_create (int /*<<< orphan*/ **,int,int,int,int,int) ; 
 int /*<<< orphan*/  audioplay_delete (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * audioplay_get_buffer (int /*<<< orphan*/ *) ; 
 int audioplay_get_latency (int /*<<< orphan*/ *) ; 
 scalar_t__ audioplay_play_buffer (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 scalar_t__ audioplay_set_dest (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usleep (int) ; 

void play_api_test(int samplerate, int bitdepth, int nchannels, int dest)
{
   AUDIOPLAY_STATE_T *st;
   int32_t ret;
   unsigned int i, j, n;
   int phase = 0;
   int inc = 256<<16;
   int dinc = 0;
   int buffer_size = (BUFFER_SIZE_SAMPLES * bitdepth * OUT_CHANNELS(nchannels))>>3;

   assert(dest == 0 || dest == 1);

   ret = audioplay_create(&st, samplerate, nchannels, bitdepth, 10, buffer_size);
   assert(ret == 0);

   ret = audioplay_set_dest(st, audio_dest[dest]);
   assert(ret == 0);

   // iterate for 5 seconds worth of packets
   for (n=0; n<((samplerate * 1000)/ BUFFER_SIZE_SAMPLES); n++)
   {
      uint8_t *buf;
      int16_t *p;
      uint32_t latency;

      while((buf = audioplay_get_buffer(st)) == NULL)
         usleep(10*1000);

      p = (int16_t *) buf;

      // fill the buffer
      for (i=0; i<BUFFER_SIZE_SAMPLES; i++)
      {
         int16_t val = SIN(phase);
         phase += inc>>16;
         inc += dinc;
         if (inc>>16 < 512)
            dinc++;
         else
            dinc--;

         for(j=0; j<OUT_CHANNELS(nchannels); j++)
         {
            if (bitdepth == 32)
               *p++ = 0;
            *p++ = val;
         }
      }

      // try and wait for a minimum latency time (in ms) before
      // sending the next packet
      while((latency = audioplay_get_latency(st)) > (samplerate * (MIN_LATENCY_TIME + CTTW_SLEEP_TIME) / 1000))
         usleep(CTTW_SLEEP_TIME*1000);

      ret = audioplay_play_buffer(st, buf, buffer_size);
      assert(ret == 0);
   }

   audioplay_delete(st);
}