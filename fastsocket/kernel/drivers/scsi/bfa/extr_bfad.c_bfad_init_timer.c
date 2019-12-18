#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {unsigned long data; int /*<<< orphan*/  function; } ;
struct bfad_s {TYPE_1__ hal_tmo; } ;

/* Variables and functions */
 int /*<<< orphan*/  BFA_TIMER_FREQ ; 
 int /*<<< orphan*/  bfad_bfa_tmo ; 
 int /*<<< orphan*/  init_timer (TYPE_1__*) ; 
 scalar_t__ jiffies ; 
 int /*<<< orphan*/  mod_timer (TYPE_1__*,scalar_t__) ; 
 scalar_t__ msecs_to_jiffies (int /*<<< orphan*/ ) ; 

void
bfad_init_timer(struct bfad_s *bfad)
{
	init_timer(&bfad->hal_tmo);
	bfad->hal_tmo.function = bfad_bfa_tmo;
	bfad->hal_tmo.data = (unsigned long)bfad;

	mod_timer(&bfad->hal_tmo,
		  jiffies + msecs_to_jiffies(BFA_TIMER_FREQ));
}