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
struct mtd_blktrans_dev {int dummy; } ;
struct hd_geometry {int /*<<< orphan*/  cylinders; int /*<<< orphan*/  sectors; int /*<<< orphan*/  heads; } ;
struct INFTLrecord {int /*<<< orphan*/  cylinders; int /*<<< orphan*/  sectors; int /*<<< orphan*/  heads; } ;

/* Variables and functions */

__attribute__((used)) static int inftl_getgeo(struct mtd_blktrans_dev *dev, struct hd_geometry *geo)
{
	struct INFTLrecord *inftl = (void *)dev;

	geo->heads = inftl->heads;
	geo->sectors = inftl->sectors;
	geo->cylinders = inftl->cylinders;

	return 0;
}