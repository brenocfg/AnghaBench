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
struct sclp_cpu_info {int dummy; } ;
struct TYPE_2__ {int length; int response_code; } ;
struct read_cpu_info_sccb {TYPE_1__ header; } ;

/* Variables and functions */
 int EIO ; 
 int ENOMEM ; 
 int EOPNOTSUPP ; 
 int GFP_DMA ; 
 int GFP_KERNEL ; 
 int /*<<< orphan*/  SCLP_CMDW_READ_CPU_INFO ; 
 int /*<<< orphan*/  SCLP_HAS_CPU_INFO ; 
 int do_sync_request (int /*<<< orphan*/ ,struct read_cpu_info_sccb*) ; 
 int /*<<< orphan*/  free_page (unsigned long) ; 
 scalar_t__ get_zeroed_page (int) ; 
 int /*<<< orphan*/  pr_warning (char*,int) ; 
 int /*<<< orphan*/  sclp_fill_cpu_info (struct sclp_cpu_info*,struct read_cpu_info_sccb*) ; 

int sclp_get_cpu_info(struct sclp_cpu_info *info)
{
	int rc;
	struct read_cpu_info_sccb *sccb;

	if (!SCLP_HAS_CPU_INFO)
		return -EOPNOTSUPP;
	sccb = (void *) get_zeroed_page(GFP_KERNEL | GFP_DMA);
	if (!sccb)
		return -ENOMEM;
	sccb->header.length = sizeof(*sccb);
	rc = do_sync_request(SCLP_CMDW_READ_CPU_INFO, sccb);
	if (rc)
		goto out;
	if (sccb->header.response_code != 0x0010) {
		pr_warning("readcpuinfo failed (response=0x%04x)\n",
			   sccb->header.response_code);
		rc = -EIO;
		goto out;
	}
	sclp_fill_cpu_info(info, sccb);
out:
	free_page((unsigned long) sccb);
	return rc;
}