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
struct aic7xxx_host {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  CLOCK_PULSE (struct aic7xxx_host*) ; 
 int /*<<< orphan*/  SEECTL ; 
 int /*<<< orphan*/  aic_outb (struct aic7xxx_host*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
release_seeprom(struct aic7xxx_host *p)
{
  /*
   * Make sure the SEEPROM is ready before we release it.
   */
  CLOCK_PULSE(p);
  aic_outb(p, 0, SEECTL);
}