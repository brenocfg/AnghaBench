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
typedef  int /*<<< orphan*/  uint8_t ;
struct sh_flctl {int index; int /*<<< orphan*/ * done_buff; } ;
struct mtd_info {int dummy; } ;

/* Variables and functions */
 struct sh_flctl* mtd_to_flctl (struct mtd_info*) ; 

__attribute__((used)) static uint8_t flctl_read_byte(struct mtd_info *mtd)
{
	struct sh_flctl *flctl = mtd_to_flctl(mtd);
	int index = flctl->index;
	uint8_t data;

	data = flctl->done_buff[index];
	flctl->index++;
	return data;
}