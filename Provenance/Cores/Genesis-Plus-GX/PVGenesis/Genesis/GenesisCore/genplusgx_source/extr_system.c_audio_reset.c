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
struct TYPE_2__ {scalar_t__** blips; } ;

/* Variables and functions */
 int /*<<< orphan*/  audio_set_equalizer () ; 
 int /*<<< orphan*/  blip_clear (scalar_t__) ; 
 scalar_t__ llp ; 
 scalar_t__ rrp ; 
 TYPE_1__ snd ; 

void audio_reset(void)
{
  int i,j;
  
  /* Clear blip buffers */
  for (i=0; i<3; i++)
  {
    for (j=0; j<2; j++)
    {
      if (snd.blips[i][j])
      {
        blip_clear(snd.blips[i][j]);
      }
    }
  }

  /* Low-Pass filter */
  llp = 0;
  rrp = 0;

  /* 3 band EQ */
  audio_set_equalizer();
}