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
struct TYPE_2__ {int /*<<< orphan*/  caps; } ;
struct osd_cdb {TYPE_1__ v1; } ;

/* Variables and functions */
 int /*<<< orphan*/  OSD_CAP_LEN ; 
 int /*<<< orphan*/  OSDv1_CAP_LEN ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,void const*,int /*<<< orphan*/ ) ; 

void osd_set_caps(struct osd_cdb *cdb, const void *caps)
{
	bool is_ver1 = true;
	/* NOTE: They start at same address */
	memcpy(&cdb->v1.caps, caps, is_ver1 ? OSDv1_CAP_LEN : OSD_CAP_LEN);
}