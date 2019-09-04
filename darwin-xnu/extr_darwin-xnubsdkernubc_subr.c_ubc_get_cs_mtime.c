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
struct vnode {struct ubc_info* v_ubcinfo; } ;
struct TYPE_2__ {int /*<<< orphan*/  tv_nsec; int /*<<< orphan*/  tv_sec; } ;
struct ubc_info {TYPE_1__ cs_mtime; } ;
struct timespec {int /*<<< orphan*/  tv_nsec; int /*<<< orphan*/  tv_sec; } ;

/* Variables and functions */
 int /*<<< orphan*/  UBCINFOEXISTS (struct vnode*) ; 

void
ubc_get_cs_mtime(
	struct vnode	*vp,
	struct timespec	*cs_mtime)
{
	struct ubc_info	*uip;

	if (! UBCINFOEXISTS(vp)) {
		cs_mtime->tv_sec = 0;
		cs_mtime->tv_nsec = 0;
		return;
	}

	uip = vp->v_ubcinfo;
	cs_mtime->tv_sec = uip->cs_mtime.tv_sec;
	cs_mtime->tv_nsec = uip->cs_mtime.tv_nsec;
}