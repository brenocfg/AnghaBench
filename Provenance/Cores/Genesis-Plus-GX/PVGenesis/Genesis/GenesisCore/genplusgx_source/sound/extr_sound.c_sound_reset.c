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
 int /*<<< orphan*/  SN76489_Reset () ; 
 int /*<<< orphan*/  YM_Reset () ; 
 int /*<<< orphan*/  fm_buffer ; 
 scalar_t__ fm_cycles_count ; 
 scalar_t__ fm_cycles_start ; 
 scalar_t__* fm_last ; 
 int /*<<< orphan*/  fm_ptr ; 

void sound_reset(void)
{
  /* reset sound chips */
  YM_Reset();
  SN76489_Reset();

  /* reset FM buffer ouput */
  fm_last[0] = fm_last[1] = 0;

  /* reset FM buffer pointer */
  fm_ptr = fm_buffer;
  
  /* reset FM cycle counters */
  fm_cycles_start = fm_cycles_count = 0;
}