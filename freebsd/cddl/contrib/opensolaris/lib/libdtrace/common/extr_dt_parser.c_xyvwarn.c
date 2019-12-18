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
typedef  int /*<<< orphan*/  va_list ;
typedef  int /*<<< orphan*/  dt_errtag_t ;
struct TYPE_2__ {scalar_t__ pcb_fileptr; int /*<<< orphan*/  pcb_filetag; int /*<<< orphan*/  pcb_region; int /*<<< orphan*/  pcb_hdl; } ;

/* Variables and functions */
 int /*<<< orphan*/  dt_errtag (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dt_set_errmsg (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  yylineno ; 
 TYPE_1__* yypcb ; 

void
xyvwarn(dt_errtag_t tag, const char *format, va_list ap)
{
	if (yypcb == NULL)
		return; /* compiler is not currently active: act as a no-op */

	dt_set_errmsg(yypcb->pcb_hdl, dt_errtag(tag), yypcb->pcb_region,
	    yypcb->pcb_filetag, yypcb->pcb_fileptr ? yylineno : 0, format, ap);
}