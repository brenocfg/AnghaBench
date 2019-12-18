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
struct gendisk {struct atari_floppy_struct* private_data; } ;
struct atari_floppy_struct {int dummy; } ;
struct TYPE_2__ {scalar_t__ wpstat; } ;

/* Variables and functions */
 TYPE_1__ UD ; 
 int /*<<< orphan*/  changed_floppies ; 
 int /*<<< orphan*/  fake_change ; 
 scalar_t__ test_bit (unsigned int,int /*<<< orphan*/ *) ; 
 struct atari_floppy_struct* unit ; 

__attribute__((used)) static int check_floppy_change(struct gendisk *disk)
{
	struct atari_floppy_struct *p = disk->private_data;
	unsigned int drive = p - unit;
	if (test_bit (drive, &fake_change)) {
		/* simulated change (e.g. after formatting) */
		return 1;
	}
	if (test_bit (drive, &changed_floppies)) {
		/* surely changed (the WP signal changed at least once) */
		return 1;
	}
	if (UD.wpstat) {
		/* WP is on -> could be changed: to be sure, buffers should be
		 * invalidated...
		 */
		return 1;
	}

	return 0;
}