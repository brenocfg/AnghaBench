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

/* Variables and functions */
 size_t BLKMULT ; 
 int /*<<< orphan*/  MAXBLK ; 
 int /*<<< orphan*/  blksz ; 
 int /*<<< orphan*/ * buf ; 
 int /*<<< orphan*/ * bufmem ; 
 int /*<<< orphan*/  rdblksz ; 

void
cp_start(void)
{
	buf = &(bufmem[BLKMULT]);
	rdblksz = blksz = MAXBLK;
}