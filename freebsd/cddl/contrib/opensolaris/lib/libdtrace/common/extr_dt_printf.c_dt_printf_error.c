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
typedef  int /*<<< orphan*/  dtrace_hdl_t ;
typedef  int /*<<< orphan*/  dt_pfargv_t ;
struct TYPE_2__ {int /*<<< orphan*/  pcb_jmpbuf; } ;

/* Variables and functions */
 int /*<<< orphan*/  dt_set_errno (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  longjmp (int /*<<< orphan*/ ,int) ; 
 TYPE_1__* yypcb ; 

__attribute__((used)) static dt_pfargv_t *
dt_printf_error(dtrace_hdl_t *dtp, int err)
{
	if (yypcb != NULL)
		longjmp(yypcb->pcb_jmpbuf, err);

	(void) dt_set_errno(dtp, err);
	return (NULL);
}