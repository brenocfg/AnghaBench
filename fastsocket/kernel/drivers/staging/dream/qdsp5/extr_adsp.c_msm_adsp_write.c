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
struct msm_adsp_module {int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int EAGAIN ; 
 int __msm_adsp_write (struct msm_adsp_module*,unsigned int,void*,size_t) ; 
 int /*<<< orphan*/  pr_warning (char*,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  udelay (int) ; 

int msm_adsp_write(struct msm_adsp_module *module, unsigned dsp_queue_addr,
		   void *cmd_buf, size_t cmd_size)
{
	int rc, retries = 0;
	do {
		rc = __msm_adsp_write(module, dsp_queue_addr, cmd_buf, cmd_size);
		if (rc == -EAGAIN)
			udelay(10);
	} while(rc == -EAGAIN && retries++ < 100);
	if (retries > 50)
		pr_warning("adsp: %s command took %d attempts: rc %d\n",
				module->name, retries, rc);
	return rc;
}