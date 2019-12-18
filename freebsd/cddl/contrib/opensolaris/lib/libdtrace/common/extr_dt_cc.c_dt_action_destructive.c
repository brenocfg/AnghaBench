#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {scalar_t__ dtad_kind; TYPE_1__* dtad_difo; } ;
typedef  TYPE_2__ dtrace_actdesc_t ;
struct TYPE_4__ {scalar_t__ dtdo_destructive; } ;

/* Variables and functions */
 scalar_t__ DTRACEACT_DIFEXPR ; 
 scalar_t__ DTRACEACT_ISDESTRUCTIVE (scalar_t__) ; 

__attribute__((used)) static int
dt_action_destructive(const dtrace_actdesc_t *ap)
{
	return (DTRACEACT_ISDESTRUCTIVE(ap->dtad_kind) || (ap->dtad_kind ==
	    DTRACEACT_DIFEXPR && ap->dtad_difo->dtdo_destructive));
}