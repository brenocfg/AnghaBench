#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {scalar_t__ ls_event; scalar_t__ ls_lock; int ls_count; } ;
typedef  TYPE_1__ lsrec_t ;

/* Variables and functions */
 int strcmp (scalar_t__,scalar_t__) ; 

__attribute__((used)) static int
lock_and_count_cmp_anywhere(lsrec_t *a, lsrec_t *b)
{
#ifndef illumos
	int cmp;
#endif

	if (a->ls_event < b->ls_event)
		return (-1);
	if (a->ls_event > b->ls_event)
		return (1);

#ifdef illumos
	if (a->ls_lock < b->ls_lock)
		return (-1);
	if (a->ls_lock > b->ls_lock)
		return (1);
#else
	cmp = strcmp(a->ls_lock, b->ls_lock);
	if (cmp != 0)
		return (cmp);
#endif

	return (b->ls_count - a->ls_count);
}