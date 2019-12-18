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
struct TYPE_2__ {int /*<<< orphan*/  cond; int /*<<< orphan*/ * buffer; int /*<<< orphan*/ * ports; } ;
typedef  TYPE_1__ jack_t ;
typedef  int jack_nframes_t ;
typedef  float jack_default_audio_sample_t ;

/* Variables and functions */
 scalar_t__ jack_port_get_buffer (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  jack_ringbuffer_read (int /*<<< orphan*/ ,char*,int) ; 
 int jack_ringbuffer_read_space (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  scond_signal (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int process_cb(jack_nframes_t nframes, void *data)
{
   int i;
   jack_nframes_t avail[2], min_avail;
   jack_t *jd = (jack_t*)data;

   if (nframes <= 0)
   {
#ifdef HAVE_THREADS
      scond_signal(jd->cond);
#endif
      return 0;
   }

   avail[0]  = jack_ringbuffer_read_space(jd->buffer[0]);
   avail[1]  = jack_ringbuffer_read_space(jd->buffer[1]);
   min_avail = ((avail[0] < avail[1]) ? avail[0] : avail[1]) / sizeof(jack_default_audio_sample_t);

   if (min_avail > nframes)
      min_avail = nframes;

   for (i = 0; i < 2; i++)
   {
      jack_nframes_t f;
      jack_default_audio_sample_t *out = (jack_default_audio_sample_t*)jack_port_get_buffer(jd->ports[i], nframes);

      jack_ringbuffer_read(jd->buffer[i], (char*)out, min_avail * sizeof(jack_default_audio_sample_t));

      for (f = min_avail; f < nframes; f++)
         out[f] = 0.0f;
   }
#ifdef HAVE_THREADS
   scond_signal(jd->cond);
#endif
   return 0;
}