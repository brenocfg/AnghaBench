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
struct TYPE_4__ {scalar_t__ ls_event; scalar_t__* ls_stack; scalar_t__ ls_caller; scalar_t__ ls_lock; } ;
typedef  TYPE_1__ lsrec_t ;

/* Variables and functions */
 int g_stkdepth ; 
 int strcmp (scalar_t__,scalar_t__) ; 

__attribute__((used)) static int
lockcmp(lsrec_t *a, lsrec_t *b)
{
	int i;

	if (a->ls_event < b->ls_event)
		return (-1);
	if (a->ls_event > b->ls_event)
		return (1);

	for (i = g_stkdepth - 1; i >= 0; i--) {
		if (a->ls_stack[i] < b->ls_stack[i])
			return (-1);
		if (a->ls_stack[i] > b->ls_stack[i])
			return (1);
	}

	if (a->ls_caller < b->ls_caller)
		return (-1);
	if (a->ls_caller > b->ls_caller)
		return (1);

#ifdef illumos
	if (a->ls_lock < b->ls_lock)
		return (-1);
	if (a->ls_lock > b->ls_lock)
		return (1);

	return (0);
#else
	return (strcmp(a->ls_lock, b->ls_lock));
#endif
}