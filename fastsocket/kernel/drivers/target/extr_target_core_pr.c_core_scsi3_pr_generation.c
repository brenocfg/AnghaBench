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
typedef  scalar_t__ u32 ;
struct TYPE_2__ {int /*<<< orphan*/  pr_generation; } ;
struct se_device {int /*<<< orphan*/  dev_reservation_lock; TYPE_1__ t10_pr; } ;

/* Variables and functions */
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static u32 core_scsi3_pr_generation(struct se_device *dev)
{
	u32 prg;

	/*
	 * PRGeneration field shall contain the value of a 32-bit wrapping
	 * counter mainted by the device server.
	 *
	 * Note that this is done regardless of Active Persist across
	 * Target PowerLoss (APTPL)
	 *
	 * See spc4r17 section 6.3.12 READ_KEYS service action
	 */
	spin_lock(&dev->dev_reservation_lock);
	prg = dev->t10_pr.pr_generation++;
	spin_unlock(&dev->dev_reservation_lock);

	return prg;
}