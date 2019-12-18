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
struct ata_device {int dummy; } ;
struct ata_acpi_gtf {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ata_acpi_clear_gtf (struct ata_device*) ; 
 int ata_acpi_run_tf (struct ata_device*,struct ata_acpi_gtf*,struct ata_acpi_gtf*) ; 
 int ata_dev_get_GTF (struct ata_device*,struct ata_acpi_gtf**) ; 

__attribute__((used)) static int ata_acpi_exec_tfs(struct ata_device *dev, int *nr_executed)
{
	struct ata_acpi_gtf *gtf = NULL, *pgtf = NULL;
	int gtf_count, i, rc;

	/* get taskfiles */
	rc = ata_dev_get_GTF(dev, &gtf);
	if (rc < 0)
		return rc;
	gtf_count = rc;

	/* execute them */
	for (i = 0; i < gtf_count; i++, gtf++) {
		rc = ata_acpi_run_tf(dev, gtf, pgtf);
		if (rc < 0)
			break;
		if (rc) {
			(*nr_executed)++;
			pgtf = gtf;
		}
	}

	ata_acpi_clear_gtf(dev);

	if (rc < 0)
		return rc;
	return 0;
}