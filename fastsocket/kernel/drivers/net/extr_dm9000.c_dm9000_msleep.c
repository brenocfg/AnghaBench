#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {scalar_t__ in_suspend; } ;
typedef  TYPE_1__ board_info_t ;

/* Variables and functions */
 int /*<<< orphan*/  mdelay (unsigned int) ; 
 int /*<<< orphan*/  msleep (unsigned int) ; 

__attribute__((used)) static void dm9000_msleep(board_info_t *db, unsigned int ms)
{
	if (db->in_suspend)
		mdelay(ms);
	else
		msleep(ms);
}