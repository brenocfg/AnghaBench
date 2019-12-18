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

/* Variables and functions */
 int /*<<< orphan*/  ASND_StopVoice (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LWP_CloseQueue (scalar_t__) ; 
 int /*<<< orphan*/  LWP_JoinThread (scalar_t__,int /*<<< orphan*/ *) ; 
 scalar_t__ LWP_THREAD_NULL ; 
 scalar_t__ LWP_TQUEUE_NULL ; 
 int /*<<< orphan*/  LWP_ThreadSignal (scalar_t__) ; 
 scalar_t__ h_oggplayer ; 
 scalar_t__ ogg_thread_running ; 
 scalar_t__ oggplayer_queue ; 

void StopOgg()
{
  ASND_StopVoice(0);
  ogg_thread_running = 0;

  if(h_oggplayer != LWP_THREAD_NULL)
  {
    if(oggplayer_queue != LWP_TQUEUE_NULL)
      LWP_ThreadSignal(oggplayer_queue);
    LWP_JoinThread(h_oggplayer, NULL);
    h_oggplayer = LWP_THREAD_NULL;
  }
  if(oggplayer_queue != LWP_TQUEUE_NULL)
  {
    LWP_CloseQueue(oggplayer_queue);
    oggplayer_queue = LWP_TQUEUE_NULL;
  }
}