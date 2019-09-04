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
struct kevent_internal_s {int /*<<< orphan*/ * ext; int /*<<< orphan*/  data; int /*<<< orphan*/  fflags; int /*<<< orphan*/  udata; int /*<<< orphan*/  flags; int /*<<< orphan*/  filter; int /*<<< orphan*/  ident; } ;

/* Variables and functions */
 int /*<<< orphan*/  snprintf (char*,size_t,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

char *
kevent_description(struct kevent_internal_s *kevp, char *s, size_t n)
{
	snprintf(s, n,
	    "kevent="
	    "{.ident=%#llx, .filter=%d, .flags=%#x, .udata=%#llx, .fflags=%#x, .data=%#llx, .ext[0]=%#llx, .ext[1]=%#llx}",
	    kevp->ident,
	    kevp->filter,
	    kevp->flags,
	    kevp->udata,
	    kevp->fflags,
	    kevp->data,
	    kevp->ext[0],
	    kevp->ext[1] );

	return (s);
}