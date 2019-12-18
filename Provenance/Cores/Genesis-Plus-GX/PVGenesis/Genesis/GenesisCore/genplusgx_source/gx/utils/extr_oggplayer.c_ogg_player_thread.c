#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {size_t pcm_indx; size_t pcmout_pos; int eof; int flag; int seek_time; int mode; int fd; int /*<<< orphan*/  vf; int /*<<< orphan*/  volume; int /*<<< orphan*/ ** pcmout; TYPE_2__* vi; scalar_t__ current_section; } ;
typedef  TYPE_1__ private_data_ogg ;
struct TYPE_5__ {int channels; int /*<<< orphan*/  rate; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASND_Pause (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ASND_SetVoice (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,void*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ ASND_StatusVoice (int /*<<< orphan*/ ) ; 
 scalar_t__ ASND_TestPointer (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  LWP_InitQueue (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  LWP_ThreadSleep (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MAX_PCMOUT ; 
 long OV_HOLE ; 
 size_t READ_SAMPLES ; 
 scalar_t__ SND_UNUSED ; 
 int /*<<< orphan*/  VOICE_MONO_16BIT ; 
 int /*<<< orphan*/  VOICE_STEREO_16BIT ; 
 int /*<<< orphan*/  ogg_add_callback ; 
 int ogg_thread_running ; 
 int /*<<< orphan*/  oggplayer_queue ; 
 int /*<<< orphan*/  ov_clear (int /*<<< orphan*/ *) ; 
 TYPE_2__* ov_info (int /*<<< orphan*/ *,int) ; 
 long ov_read (int /*<<< orphan*/ *,void*,int /*<<< orphan*/ ,scalar_t__*) ; 
 int /*<<< orphan*/  ov_time_seek (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  usleep (int) ; 

__attribute__((used)) static void * ogg_player_thread(private_data_ogg * priv)
{
  int first_time = 1;
  long ret;

  /* init */
  LWP_InitQueue(&oggplayer_queue);

  priv[0].vi = ov_info(&priv[0].vf, -1);

  ASND_Pause(0);

  priv[0].pcm_indx = 0;
  priv[0].pcmout_pos = 0;
  priv[0].eof = 0;
  priv[0].flag = 0;
  priv[0].current_section = 0;

  ogg_thread_running = 1;

  while (!priv[0].eof && ogg_thread_running)
  {
    if (priv[0].flag)
      LWP_ThreadSleep(oggplayer_queue); /* wait only when i have samples to send */

    if (priv[0].flag == 0) /* wait to all samples are sended */
    {
      if (ASND_TestPointer(0, priv[0].pcmout[priv[0].pcmout_pos])
          && ASND_StatusVoice(0) != SND_UNUSED)
      {
        priv[0].flag |= 64;
        continue;
      }
      if (priv[0].pcm_indx < READ_SAMPLES)
      {
        priv[0].flag = 3;

        if (priv[0].seek_time >= 0)
        {
          ov_time_seek(&priv[0].vf, priv[0].seek_time);
          priv[0].seek_time = -1;
        }

        ret
            = ov_read(
                &priv[0].vf,
                (void *) &priv[0].pcmout[priv[0].pcmout_pos][priv[0].pcm_indx],
                MAX_PCMOUT,/*0,2,1,*/&priv[0].current_section);
        priv[0].flag &= 192;
        if (ret == 0)
        {
          /* EOF */
          if (priv[0].mode & 1)
            ov_time_seek(&priv[0].vf, 0); /* repeat */
          else
            priv[0].eof = 1; /* stops */
        }
        else if (ret < 0)
        {
          /* error in the stream.  Not a problem, just reporting it in
           case we (the app) cares.  In this case, we don't. */
          if (ret != OV_HOLE)
          {
            if (priv[0].mode & 1)
              ov_time_seek(&priv[0].vf, 0); /* repeat */
            else
              priv[0].eof = 1; /* stops */
          }
        }
        else
        {
          /* we don't bother dealing with sample rate changes, etc, but
           you'll have to */
          priv[0].pcm_indx += ret >> 1; /* get 16 bits samples */
        }
      }
      else
        priv[0].flag = 1;
    }

    if (priv[0].flag == 1)
    {
      if (ASND_StatusVoice(0) == SND_UNUSED || first_time)
      {
        first_time = 0;
        if (priv[0].vi->channels == 2)
        {
          ASND_SetVoice(0, VOICE_STEREO_16BIT, priv[0].vi->rate, 0,
              (void *) priv[0].pcmout[priv[0].pcmout_pos],
              priv[0].pcm_indx << 1, priv[0].volume,
              priv[0].volume, ogg_add_callback);
          priv[0].pcmout_pos ^= 1;
          priv[0].pcm_indx = 0;
          priv[0].flag = 0;
        }
        else
        {
          ASND_SetVoice(0, VOICE_MONO_16BIT, priv[0].vi->rate, 0,
              (void *) priv[0].pcmout[priv[0].pcmout_pos],
              priv[0].pcm_indx << 1, priv[0].volume,
              priv[0].volume, ogg_add_callback);
          priv[0].pcmout_pos ^= 1;
          priv[0].pcm_indx = 0;
          priv[0].flag = 0;
        }
      }
    }
    usleep(10);
  }
  ov_clear(&priv[0].vf);
  priv[0].fd = -1;
  priv[0].pcm_indx = 0;

  return 0;
}