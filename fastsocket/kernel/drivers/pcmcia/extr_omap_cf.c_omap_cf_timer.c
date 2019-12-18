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
struct omap_cf_socket {unsigned int present; int /*<<< orphan*/  timer; scalar_t__ active; int /*<<< orphan*/  socket; } ;

/* Variables and functions */
 scalar_t__ POLL_INTERVAL ; 
 int /*<<< orphan*/  SS_DETECT ; 
 int /*<<< orphan*/  driver_name ; 
 scalar_t__ jiffies ; 
 int /*<<< orphan*/  mod_timer (int /*<<< orphan*/ *,scalar_t__) ; 
 unsigned int omap_cf_present () ; 
 int /*<<< orphan*/  pcmcia_parse_events (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_debug (char*,int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static void omap_cf_timer(unsigned long _cf)
{
	struct omap_cf_socket	*cf = (void *) _cf;
	unsigned		present = omap_cf_present();

	if (present != cf->present) {
		cf->present = present;
		pr_debug("%s: card %s\n", driver_name,
			present ? "present" : "gone");
		pcmcia_parse_events(&cf->socket, SS_DETECT);
	}

	if (cf->active)
		mod_timer(&cf->timer, jiffies + POLL_INTERVAL);
}