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
typedef  TYPE_1__* proc_t ;
typedef  int /*<<< orphan*/  boolean_t ;
struct TYPE_4__ {int /*<<< orphan*/  p_lflag; } ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 scalar_t__ ISSET (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_1__* PROC_NULL ; 
 int /*<<< orphan*/  P_LTRACED ; 
 int /*<<< orphan*/  TRUE ; 

boolean_t
proc_send_synchronous_EXC_RESOURCE(proc_t p)
{
	if (p == PROC_NULL)
		return FALSE;

	/* Send sync EXC_RESOURCE if the process is traced */
	if (ISSET(p->p_lflag, P_LTRACED)) {
		return TRUE;
	}
	return FALSE;
}