#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  client; int /*<<< orphan*/ * ports; } ;
typedef  TYPE_1__ jack_t ;
struct TYPE_6__ {int max; } ;
typedef  TYPE_2__ jack_latency_range_t ;
typedef  int /*<<< orphan*/  jack_default_audio_sample_t ;

/* Variables and functions */
 int /*<<< orphan*/  JackPlaybackLatency ; 
 int /*<<< orphan*/  RARCH_LOG (char*,int) ; 
 int jack_get_buffer_size (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  jack_port_get_latency_range (int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_2__*) ; 

__attribute__((used)) static size_t find_buffersize(jack_t *jd, int latency, unsigned out_rate)
{
   jack_latency_range_t range;
   int i, buffer_frames, min_buffer_frames;
   int jack_latency     = 0;
   int           frames = latency * out_rate / 1000;

   for (i = 0; i < 2; i++)
   {
      jack_port_get_latency_range(jd->ports[i], JackPlaybackLatency, &range);
      if ((int)range.max > jack_latency)
         jack_latency = range.max;
   }

   RARCH_LOG("[JACK]: Jack latency is %d frames.\n", jack_latency);

   buffer_frames     = frames - jack_latency;
   min_buffer_frames = jack_get_buffer_size(jd->client) * 2;

   RARCH_LOG("[JACK]: Minimum buffer size is %d frames.\n", min_buffer_frames);

   if (buffer_frames < min_buffer_frames)
      buffer_frames = min_buffer_frames;

   return buffer_frames * sizeof(jack_default_audio_sample_t);
}