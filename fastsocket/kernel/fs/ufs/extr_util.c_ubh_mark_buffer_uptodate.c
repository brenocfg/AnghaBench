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
struct ufs_buffer_head {unsigned int count; int /*<<< orphan*/ * bh; } ;

/* Variables and functions */
 int /*<<< orphan*/  clear_buffer_uptodate (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_buffer_uptodate (int /*<<< orphan*/ ) ; 

void ubh_mark_buffer_uptodate (struct ufs_buffer_head * ubh, int flag)
{
	unsigned i;
	if (!ubh)
		return;
	if (flag) {
		for ( i = 0; i < ubh->count; i++ )
			set_buffer_uptodate (ubh->bh[i]);
	} else {
		for ( i = 0; i < ubh->count; i++ )
			clear_buffer_uptodate (ubh->bh[i]);
	}
}