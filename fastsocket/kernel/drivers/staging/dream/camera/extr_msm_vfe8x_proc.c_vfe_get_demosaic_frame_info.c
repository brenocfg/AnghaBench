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
struct vfe_irq_thread_msg {int /*<<< orphan*/  demosaicStatus; } ;
struct vfe_frame_bpc_info {int /*<<< orphan*/  RedBlueBadPixelCount; int /*<<< orphan*/  redBlueDefectPixelCount; int /*<<< orphan*/  greenBadPixelCount; int /*<<< orphan*/  greenDefectPixelCount; } ;
struct vfe_bps_info {int /*<<< orphan*/  RedBlueBadPixelCount; int /*<<< orphan*/  redBlueDefectPixelCount; int /*<<< orphan*/  greenBadPixelCount; int /*<<< orphan*/  greenDefectPixelCount; } ;
typedef  int /*<<< orphan*/  rc ;
typedef  int /*<<< orphan*/  bpcInfoTemp ;

/* Variables and functions */
 int /*<<< orphan*/  memset (struct vfe_frame_bpc_info*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static struct vfe_frame_bpc_info
vfe_get_demosaic_frame_info(struct vfe_irq_thread_msg *in)
{
	struct vfe_bps_info     bpcInfoTemp;
	struct vfe_frame_bpc_info rc;

	memset(&rc, 0, sizeof(rc));
	memset(&bpcInfoTemp, 0, sizeof(bpcInfoTemp));

	bpcInfoTemp =
		*((struct vfe_bps_info *)(&(in->demosaicStatus)));

	rc.greenDefectPixelCount    =
		bpcInfoTemp.greenBadPixelCount;

	rc.redBlueDefectPixelCount  =
		bpcInfoTemp.RedBlueBadPixelCount;

	return rc;
}