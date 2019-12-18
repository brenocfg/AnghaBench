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
struct ata_queued_cmd {TYPE_1__* dev; int /*<<< orphan*/  ap; } ;
struct TYPE_2__ {int /*<<< orphan*/  devno; } ;

/* Variables and functions */
 unsigned int ata_sff_qc_issue (struct ata_queued_cmd*) ; 
 int /*<<< orphan*/  it821x_passthru_dev_select (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static unsigned int it821x_passthru_qc_issue(struct ata_queued_cmd *qc)
{
	it821x_passthru_dev_select(qc->ap, qc->dev->devno);
	return ata_sff_qc_issue(qc);
}