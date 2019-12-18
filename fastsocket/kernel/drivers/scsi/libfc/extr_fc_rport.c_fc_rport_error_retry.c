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
struct fc_rport_priv {scalar_t__ retries; int /*<<< orphan*/  retry_work; TYPE_1__* local_port; } ;
struct fc_frame {int dummy; } ;
struct TYPE_2__ {scalar_t__ max_rport_retry_count; } ;

/* Variables and functions */
 unsigned long FC_DEF_E_D_TOV ; 
 int /*<<< orphan*/  FC_EX_CLOSED ; 
 int /*<<< orphan*/  FC_EX_TIMEOUT ; 
 int /*<<< orphan*/  FC_RPORT_DBG (struct fc_rport_priv*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PTR_ERR (struct fc_frame*) ; 
 int /*<<< orphan*/  fc_rport_error (struct fc_rport_priv*,struct fc_frame*) ; 
 int /*<<< orphan*/  fc_rport_state (struct fc_rport_priv*) ; 
 int /*<<< orphan*/  schedule_delayed_work (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static void fc_rport_error_retry(struct fc_rport_priv *rdata,
				 struct fc_frame *fp)
{
	unsigned long delay = FC_DEF_E_D_TOV;

	/* make sure this isn't an FC_EX_CLOSED error, never retry those */
	if (PTR_ERR(fp) == -FC_EX_CLOSED)
		goto out;

	if (rdata->retries < rdata->local_port->max_rport_retry_count) {
		FC_RPORT_DBG(rdata, "Error %ld in state %s, retrying\n",
			     PTR_ERR(fp), fc_rport_state(rdata));
		rdata->retries++;
		/* no additional delay on exchange timeouts */
		if (PTR_ERR(fp) == -FC_EX_TIMEOUT)
			delay = 0;
		schedule_delayed_work(&rdata->retry_work, delay);
		return;
	}

out:
	fc_rport_error(rdata, fp);
}