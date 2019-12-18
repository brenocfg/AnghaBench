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
struct vfe_irq_thread_msg {int /*<<< orphan*/  asfMaxEdge; } ;
struct vfe_frame_asf_info {int /*<<< orphan*/  maxEdge; int /*<<< orphan*/  asfMaxEdge; int /*<<< orphan*/  HBICount; int /*<<< orphan*/  asfHbiCount; } ;
struct vfe_asf_info {int /*<<< orphan*/  maxEdge; int /*<<< orphan*/  asfMaxEdge; int /*<<< orphan*/  HBICount; int /*<<< orphan*/  asfHbiCount; } ;
typedef  int /*<<< orphan*/  rc ;
typedef  int /*<<< orphan*/  asfInfoTemp ;

/* Variables and functions */
 int /*<<< orphan*/  memset (struct vfe_frame_asf_info*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static struct vfe_frame_asf_info
vfe_get_asf_frame_info(struct vfe_irq_thread_msg *in)
{
	struct vfe_asf_info     asfInfoTemp;
	struct vfe_frame_asf_info rc;

	memset(&rc, 0, sizeof(rc));
	memset(&asfInfoTemp, 0, sizeof(asfInfoTemp));

	asfInfoTemp =
		*((struct vfe_asf_info *)(&(in->asfMaxEdge)));

	rc.asfHbiCount = asfInfoTemp.HBICount;
	rc.asfMaxEdge  = asfInfoTemp.maxEdge;

	return rc;
}