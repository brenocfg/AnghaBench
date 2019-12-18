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
struct ssfdcr_record {int /*<<< orphan*/  cylinders; int /*<<< orphan*/  sectors; int /*<<< orphan*/  heads; } ;
struct mtd_blktrans_dev {int dummy; } ;
struct hd_geometry {int /*<<< orphan*/  cylinders; int /*<<< orphan*/  sectors; int /*<<< orphan*/  heads; } ;

/* Variables and functions */
 int /*<<< orphan*/  DEBUG (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MTD_DEBUG_LEVEL1 ; 

__attribute__((used)) static int ssfdcr_getgeo(struct mtd_blktrans_dev *dev,  struct hd_geometry *geo)
{
	struct ssfdcr_record *ssfdc = (struct ssfdcr_record *)dev;

	DEBUG(MTD_DEBUG_LEVEL1, "SSFDC_RO: ssfdcr_getgeo() C=%d, H=%d, S=%d\n",
			ssfdc->cylinders, ssfdc->heads, ssfdc->sectors);

	geo->heads = ssfdc->heads;
	geo->sectors = ssfdc->sectors;
	geo->cylinders = ssfdc->cylinders;

	return 0;
}