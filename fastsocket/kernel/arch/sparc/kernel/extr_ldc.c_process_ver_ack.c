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
struct ldc_version {scalar_t__ major; scalar_t__ minor; } ;
struct ldc_channel {scalar_t__ hs_state; struct ldc_version ver; } ;

/* Variables and functions */
 int /*<<< orphan*/  HS ; 
 scalar_t__ LDC_HS_GOTVERS ; 
 int ldc_abort (struct ldc_channel*) ; 
 int /*<<< orphan*/  ldcdbg (int /*<<< orphan*/ ,char*,scalar_t__,scalar_t__) ; 
 scalar_t__ send_rts (struct ldc_channel*) ; 

__attribute__((used)) static int process_ver_ack(struct ldc_channel *lp, struct ldc_version *vp)
{
	ldcdbg(HS, "GOT VERSION ACK major[%x] minor[%x]\n",
	       vp->major, vp->minor);

	if (lp->hs_state == LDC_HS_GOTVERS) {
		if (lp->ver.major != vp->major ||
		    lp->ver.minor != vp->minor)
			return ldc_abort(lp);
	} else {
		lp->ver = *vp;
		lp->hs_state = LDC_HS_GOTVERS;
	}
	if (send_rts(lp))
		return ldc_abort(lp);
	return 0;
}