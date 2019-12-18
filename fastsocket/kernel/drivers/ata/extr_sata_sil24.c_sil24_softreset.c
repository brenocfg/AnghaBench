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
struct ata_taskfile {int dummy; } ;
struct ata_port {int dummy; } ;
struct ata_link {int /*<<< orphan*/  device; struct ata_port* ap; } ;

/* Variables and functions */
 int /*<<< orphan*/  DPRINTK (char*,...) ; 
 int EBUSY ; 
 int EIO ; 
 int /*<<< orphan*/  KERN_ERR ; 
 int /*<<< orphan*/  PRB_CTRL_SRST ; 
 unsigned int ata_dev_classify (struct ata_taskfile*) ; 
 int /*<<< orphan*/  ata_link_printk (struct ata_link*,int /*<<< orphan*/ ,char*,char const*) ; 
 int /*<<< orphan*/  ata_tf_init (int /*<<< orphan*/ ,struct ata_taskfile*) ; 
 scalar_t__ jiffies ; 
 unsigned long jiffies_to_msecs (scalar_t__) ; 
 int sata_srst_pmp (struct ata_link*) ; 
 int sil24_exec_polled_cmd (struct ata_port*,int,struct ata_taskfile*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned long) ; 
 scalar_t__ sil24_init_port (struct ata_port*) ; 
 int /*<<< orphan*/  sil24_read_tf (struct ata_port*,int /*<<< orphan*/ ,struct ata_taskfile*) ; 
 scalar_t__ time_after (unsigned long,scalar_t__) ; 

__attribute__((used)) static int sil24_softreset(struct ata_link *link, unsigned int *class,
			   unsigned long deadline)
{
	struct ata_port *ap = link->ap;
	int pmp = sata_srst_pmp(link);
	unsigned long timeout_msec = 0;
	struct ata_taskfile tf;
	const char *reason;
	int rc;

	DPRINTK("ENTER\n");

	/* put the port into known state */
	if (sil24_init_port(ap)) {
		reason = "port not ready";
		goto err;
	}

	/* do SRST */
	if (time_after(deadline, jiffies))
		timeout_msec = jiffies_to_msecs(deadline - jiffies);

	ata_tf_init(link->device, &tf);	/* doesn't really matter */
	rc = sil24_exec_polled_cmd(ap, pmp, &tf, 0, PRB_CTRL_SRST,
				   timeout_msec);
	if (rc == -EBUSY) {
		reason = "timeout";
		goto err;
	} else if (rc) {
		reason = "SRST command error";
		goto err;
	}

	sil24_read_tf(ap, 0, &tf);
	*class = ata_dev_classify(&tf);

	DPRINTK("EXIT, class=%u\n", *class);
	return 0;

 err:
	ata_link_printk(link, KERN_ERR, "softreset failed (%s)\n", reason);
	return -EIO;
}