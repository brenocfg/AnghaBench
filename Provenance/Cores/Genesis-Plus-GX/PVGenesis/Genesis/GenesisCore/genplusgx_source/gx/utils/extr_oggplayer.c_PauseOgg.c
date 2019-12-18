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
struct TYPE_2__ {int flag; } ;

/* Variables and functions */
 int /*<<< orphan*/  LWP_ThreadSignal (int /*<<< orphan*/ ) ; 
 scalar_t__ ogg_thread_running ; 
 int /*<<< orphan*/  oggplayer_queue ; 
 TYPE_1__ private_ogg ; 

void PauseOgg(int pause)
{
  if (pause)
  {
    private_ogg.flag |= 128;
  }
  else
  {
    if (private_ogg.flag & 128)
    {
      private_ogg.flag |= 64;
      private_ogg.flag &= ~128;
      if (ogg_thread_running > 0)
      {
        LWP_ThreadSignal(oggplayer_queue);
      }
    }
  }
}