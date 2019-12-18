#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int status; } ;
struct ipw2100_priv {int status; TYPE_1__ wstats; } ;
struct TYPE_4__ {int status; int name; int /*<<< orphan*/  (* cb ) (struct ipw2100_priv*,int) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  IPW_DEBUG_INFO (char*) ; 
 int /*<<< orphan*/  IPW_DEBUG_NOTIF (char*,int) ; 
 int IPW_STATE_SCANNING ; 
 int STATUS_ASSOCIATED ; 
 int STATUS_SCANNING ; 
 int /*<<< orphan*/  schedule_reset (struct ipw2100_priv*) ; 
 TYPE_2__* status_handlers ; 
 int /*<<< orphan*/  stub1 (struct ipw2100_priv*,int) ; 

__attribute__((used)) static void isr_status_change(struct ipw2100_priv *priv, int status)
{
	int i;

	if (status == IPW_STATE_SCANNING &&
	    priv->status & STATUS_ASSOCIATED &&
	    !(priv->status & STATUS_SCANNING)) {
		IPW_DEBUG_INFO("Scan detected while associated, with "
			       "no scan request.  Restarting firmware.\n");

		/* Wake up any sleeping jobs */
		schedule_reset(priv);
	}

	for (i = 0; status_handlers[i].status != -1; i++) {
		if (status == status_handlers[i].status) {
			IPW_DEBUG_NOTIF("Status change: %s\n",
					status_handlers[i].name);
			if (status_handlers[i].cb)
				status_handlers[i].cb(priv, status);
			priv->wstats.status = status;
			return;
		}
	}

	IPW_DEBUG_NOTIF("unknown status received: %04x\n", status);
}