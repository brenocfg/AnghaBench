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
struct pd_unit {int sectors; int heads; scalar_t__ can_lba; } ;

/* Variables and functions */
 int /*<<< orphan*/  pd_send_command (struct pd_unit*,int,int,int,int,int,int) ; 

__attribute__((used)) static void pd_ide_command(struct pd_unit *disk, int func, int block, int count)
{
	int c1, c0, h, s;

	if (disk->can_lba) {
		s = block & 255;
		c0 = (block >>= 8) & 255;
		c1 = (block >>= 8) & 255;
		h = ((block >>= 8) & 15) + 0x40;
	} else {
		s = (block % disk->sectors) + 1;
		h = (block /= disk->sectors) % disk->heads;
		c0 = (block /= disk->heads) % 256;
		c1 = (block >>= 8);
	}
	pd_send_command(disk, count, s, h, c0, c1, func);
}