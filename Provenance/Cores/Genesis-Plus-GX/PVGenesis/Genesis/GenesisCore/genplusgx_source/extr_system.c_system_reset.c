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
 int /*<<< orphan*/  audio_reset () ; 
 int /*<<< orphan*/  gen_reset (int) ; 
 int /*<<< orphan*/  io_reset () ; 
 int /*<<< orphan*/  render_reset () ; 
 int /*<<< orphan*/  sound_reset () ; 
 int /*<<< orphan*/  vdp_reset () ; 

void system_reset(void)
{
  gen_reset(1);
  io_reset();
  render_reset();
  vdp_reset();
  sound_reset();
  audio_reset();
}