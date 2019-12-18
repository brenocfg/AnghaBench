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
struct ata_taskfile {int command; int feature; int /*<<< orphan*/  device; int /*<<< orphan*/  lbah; int /*<<< orphan*/  lbam; int /*<<< orphan*/  lbal; int /*<<< orphan*/  nsect; } ;
struct ata_device {int dummy; } ;
struct ata_acpi_gtf {scalar_t__* tf; } ;
typedef  int /*<<< orphan*/  msg ;

/* Variables and functions */
#define  AC_ERR_DEV 128 
 int /*<<< orphan*/  DMA_NONE ; 
 int EIO ; 
 char* KERN_DEBUG ; 
 char* KERN_ERR ; 
 char* KERN_INFO ; 
 int /*<<< orphan*/  ata_acpi_filter_tf (struct ata_device*,struct ata_taskfile*,struct ata_taskfile*) ; 
 int /*<<< orphan*/  ata_acpi_gtf_to_tf (struct ata_device*,struct ata_acpi_gtf const*,struct ata_taskfile*) ; 
 int /*<<< orphan*/  ata_dev_printk (struct ata_device*,char const*,char*,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char const*,char*) ; 
 unsigned int ata_exec_internal (struct ata_device*,struct ata_taskfile*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 char* ata_get_cmd_descript (int) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,...) ; 

__attribute__((used)) static int ata_acpi_run_tf(struct ata_device *dev,
			   const struct ata_acpi_gtf *gtf,
			   const struct ata_acpi_gtf *prev_gtf)
{
	struct ata_taskfile *pptf = NULL;
	struct ata_taskfile tf, ptf, rtf;
	unsigned int err_mask;
	const char *level;
	const char *descr;
	char msg[60];
	int rc;

	if ((gtf->tf[0] == 0) && (gtf->tf[1] == 0) && (gtf->tf[2] == 0)
	    && (gtf->tf[3] == 0) && (gtf->tf[4] == 0) && (gtf->tf[5] == 0)
	    && (gtf->tf[6] == 0))
		return 0;

	ata_acpi_gtf_to_tf(dev, gtf, &tf);
	if (prev_gtf) {
		ata_acpi_gtf_to_tf(dev, prev_gtf, &ptf);
		pptf = &ptf;
	}

	if (!ata_acpi_filter_tf(dev, &tf, pptf)) {
		rtf = tf;
		err_mask = ata_exec_internal(dev, &rtf, NULL,
					     DMA_NONE, NULL, 0, 0);

		switch (err_mask) {
		case 0:
			level = KERN_DEBUG;
			snprintf(msg, sizeof(msg), "succeeded");
			rc = 1;
			break;

		case AC_ERR_DEV:
			level = KERN_INFO;
			snprintf(msg, sizeof(msg),
				 "rejected by device (Stat=0x%02x Err=0x%02x)",
				 rtf.command, rtf.feature);
			rc = 0;
			break;

		default:
			level = KERN_ERR;
			snprintf(msg, sizeof(msg),
				 "failed (Emask=0x%x Stat=0x%02x Err=0x%02x)",
				 err_mask, rtf.command, rtf.feature);
			rc = -EIO;
			break;
		}
	} else {
		level = KERN_INFO;
		snprintf(msg, sizeof(msg), "filtered out");
		rc = 0;
	}
	descr = ata_get_cmd_descript(tf.command);

	ata_dev_printk(dev, level,
		       "ACPI cmd %02x/%02x:%02x:%02x:%02x:%02x:%02x (%s) %s\n",
		       tf.command, tf.feature, tf.nsect, tf.lbal,
		       tf.lbam, tf.lbah, tf.device,
		       (descr ? descr : "unknown"), msg);

	return rc;
}