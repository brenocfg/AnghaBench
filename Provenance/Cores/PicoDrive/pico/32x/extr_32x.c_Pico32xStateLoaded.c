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
struct TYPE_2__ {int /*<<< orphan*/  m68krcycles_done; } ;

/* Variables and functions */
 int /*<<< orphan*/  Pico32xMemStateLoaded () ; 
 int /*<<< orphan*/  SekCyclesDone () ; 
 int /*<<< orphan*/  p32x_pwm_state_loaded () ; 
 int /*<<< orphan*/  p32x_run_events (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  p32x_update_irls (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 TYPE_1__* sh2s ; 

void Pico32xStateLoaded(int is_early)
{
  if (is_early) {
    Pico32xMemStateLoaded();
    return;
  }

  sh2s[0].m68krcycles_done = sh2s[1].m68krcycles_done = SekCyclesDone();
  p32x_update_irls(NULL, SekCyclesDone());
  p32x_pwm_state_loaded();
  p32x_run_events(SekCyclesDone());
}