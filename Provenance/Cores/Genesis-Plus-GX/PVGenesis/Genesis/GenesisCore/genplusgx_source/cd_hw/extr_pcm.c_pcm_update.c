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
struct TYPE_2__ {scalar_t__ cycles; } ;

/* Variables and functions */
 int /*<<< orphan*/ * blip ; 
 unsigned int blip_clocks_needed (int /*<<< orphan*/ ,unsigned int) ; 
 TYPE_1__ pcm ; 
 int /*<<< orphan*/  pcm_run (unsigned int) ; 

void pcm_update(unsigned int samples)
{
  /* get number of internal clocks (samples) needed */
  unsigned int clocks = blip_clocks_needed(blip[0], samples);

  /* run PCM chip */
  if (clocks > 0)
  {
    pcm_run(clocks);
  }

  /* reset PCM master clocks counter */
  pcm.cycles = 0;
}