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
struct elfcopy {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ac_read_objs (struct elfcopy*,int) ; 
 int /*<<< orphan*/  ac_write_cleanup (struct elfcopy*) ; 
 int /*<<< orphan*/  ac_write_objs (struct elfcopy*,int) ; 
 int /*<<< orphan*/  sync_ar (struct elfcopy*) ; 

void
ac_create_ar(struct elfcopy *ecp, int ifd, int ofd)
{

	ac_read_objs(ecp, ifd);
	sync_ar(ecp);
	ac_write_objs(ecp, ofd);
	ac_write_cleanup(ecp);
}