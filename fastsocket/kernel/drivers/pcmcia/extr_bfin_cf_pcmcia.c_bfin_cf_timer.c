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
struct bfin_cf_socket {unsigned short present; int /*<<< orphan*/  timer; scalar_t__ active; int /*<<< orphan*/  socket; TYPE_1__* pdev; int /*<<< orphan*/  cd_pfx; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 scalar_t__ POLL_INTERVAL ; 
 int /*<<< orphan*/  SS_DETECT ; 
 unsigned short bfin_cf_present (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*,char*) ; 
 scalar_t__ jiffies ; 
 int /*<<< orphan*/  mod_timer (int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  pcmcia_parse_events (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void bfin_cf_timer(unsigned long _cf)
{
	struct bfin_cf_socket *cf = (void *)_cf;
	unsigned short present = bfin_cf_present(cf->cd_pfx);

	if (present != cf->present) {
		cf->present = present;
		dev_dbg(&cf->pdev->dev, ": card %s\n",
			 present ? "present" : "gone");
		pcmcia_parse_events(&cf->socket, SS_DETECT);
	}

	if (cf->active)
		mod_timer(&cf->timer, jiffies + POLL_INTERVAL);
}