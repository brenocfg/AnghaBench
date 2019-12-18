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
struct TYPE_2__ {int length; int response_code; } ;
struct chp_cfg_sccb {TYPE_1__ header; } ;
typedef  int /*<<< orphan*/  sclp_cmdw_t ;

/* Variables and functions */
 int EIO ; 
 int ENOMEM ; 
 int EOPNOTSUPP ; 
 int GFP_DMA ; 
 int GFP_KERNEL ; 
 int /*<<< orphan*/  SCLP_HAS_CHP_RECONFIG ; 
 int do_sync_request (int /*<<< orphan*/ ,struct chp_cfg_sccb*) ; 
 int /*<<< orphan*/  free_page (unsigned long) ; 
 scalar_t__ get_zeroed_page (int) ; 
 int /*<<< orphan*/  pr_warning (char*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int do_chp_configure(sclp_cmdw_t cmd)
{
	struct chp_cfg_sccb *sccb;
	int rc;

	if (!SCLP_HAS_CHP_RECONFIG)
		return -EOPNOTSUPP;
	/* Prepare sccb. */
	sccb = (struct chp_cfg_sccb *) get_zeroed_page(GFP_KERNEL | GFP_DMA);
	if (!sccb)
		return -ENOMEM;
	sccb->header.length = sizeof(*sccb);
	rc = do_sync_request(cmd, sccb);
	if (rc)
		goto out;
	switch (sccb->header.response_code) {
	case 0x0020:
	case 0x0120:
	case 0x0440:
	case 0x0450:
		break;
	default:
		pr_warning("configure channel-path failed "
			   "(cmd=0x%08x, response=0x%04x)\n", cmd,
			   sccb->header.response_code);
		rc = -EIO;
		break;
	}
out:
	free_page((unsigned long) sccb);
	return rc;
}