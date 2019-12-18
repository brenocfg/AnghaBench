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
struct gendisk {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  cd_info; } ;

/* Variables and functions */
 int cdrom_media_changed (int /*<<< orphan*/ ) ; 
 TYPE_1__ gd ; 

__attribute__((used)) static int gdrom_bdops_mediachanged(struct gendisk *disk)
{
	return cdrom_media_changed(gd.cd_info);
}