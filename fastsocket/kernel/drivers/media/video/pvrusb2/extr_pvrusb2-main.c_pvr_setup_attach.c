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
struct pvr2_context {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  class_ptr ; 
 int /*<<< orphan*/  pvr2_dvb_create (struct pvr2_context*) ; 
 int /*<<< orphan*/  pvr2_sysfs_create (struct pvr2_context*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pvr2_v4l2_create (struct pvr2_context*) ; 

__attribute__((used)) static void pvr_setup_attach(struct pvr2_context *pvr)
{
	/* Create association with v4l layer */
	pvr2_v4l2_create(pvr);
#ifdef CONFIG_VIDEO_PVRUSB2_DVB
	/* Create association with dvb layer */
	pvr2_dvb_create(pvr);
#endif
#ifdef CONFIG_VIDEO_PVRUSB2_SYSFS
	pvr2_sysfs_create(pvr,class_ptr);
#endif /* CONFIG_VIDEO_PVRUSB2_SYSFS */
}