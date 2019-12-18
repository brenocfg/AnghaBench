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
 int /*<<< orphan*/  gen_init () ; 
 int /*<<< orphan*/  io_init () ; 
 int /*<<< orphan*/  render_init () ; 
 int /*<<< orphan*/  sound_init () ; 
 int /*<<< orphan*/  vdp_init () ; 

void system_init(void)
{
  gen_init();
  io_init();
  vdp_init();
  render_init();
  sound_init();
}