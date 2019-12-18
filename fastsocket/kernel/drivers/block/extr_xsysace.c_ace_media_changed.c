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
struct gendisk {struct ace_device* private_data; } ;
struct ace_device {int media_change; int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,int) ; 

__attribute__((used)) static int ace_media_changed(struct gendisk *gd)
{
	struct ace_device *ace = gd->private_data;
	dev_dbg(ace->dev, "ace_media_changed(): %i\n", ace->media_change);

	return ace->media_change;
}