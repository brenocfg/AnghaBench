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
struct ide_tape_obj {int dummy; } ;
struct gendisk {int dummy; } ;
typedef  int /*<<< orphan*/  fmode_t ;

/* Variables and functions */
 struct ide_tape_obj* ide_drv_g (struct gendisk*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ide_tape_obj ; 
 int /*<<< orphan*/  ide_tape_put (struct ide_tape_obj*) ; 

__attribute__((used)) static int idetape_release(struct gendisk *disk, fmode_t mode)
{
	struct ide_tape_obj *tape = ide_drv_g(disk, ide_tape_obj);

	ide_tape_put(tape);
	return 0;
}