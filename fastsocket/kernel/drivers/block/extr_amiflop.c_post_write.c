#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {scalar_t__ dsklen; } ;
struct TYPE_3__ {scalar_t__ dirty; } ;

/* Variables and functions */
 scalar_t__ block_flag ; 
 TYPE_2__ custom ; 
 int /*<<< orphan*/  fd_deselect (unsigned long) ; 
 int /*<<< orphan*/  printk (char*,unsigned long) ; 
 int /*<<< orphan*/  rel_fdc () ; 
 TYPE_1__* unit ; 
 int /*<<< orphan*/  wait_fd_block ; 
 int /*<<< orphan*/  wake_up (int /*<<< orphan*/ *) ; 
 scalar_t__ writefromint ; 
 scalar_t__ writepending ; 

__attribute__((used)) static void post_write (unsigned long drive)
{
#ifdef DEBUG
	printk("post_write for drive %ld\n",drive);
#endif
	drive &= 3;
	custom.dsklen = 0;
	block_flag = 0;
	writepending = 0;
	writefromint = 0;
	unit[drive].dirty = 0;
	wake_up(&wait_fd_block);
	fd_deselect(drive);
	rel_fdc(); /* corresponds to get_fdc() in raw_write */
}