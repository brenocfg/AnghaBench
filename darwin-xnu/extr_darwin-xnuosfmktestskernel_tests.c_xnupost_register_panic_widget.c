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
typedef  int /*<<< orphan*/ * xt_panic_widget_func ;
typedef  int /*<<< orphan*/  kern_return_t ;
struct TYPE_2__ {char const* xtp_func_name; void** xtp_outval_p; int /*<<< orphan*/ * xtp_func; int /*<<< orphan*/ * xtp_context_p; } ;

/* Variables and functions */
 int /*<<< orphan*/  KERN_RESOURCE_SHORTAGE ; 
 int /*<<< orphan*/  KERN_SUCCESS ; 
 TYPE_1__ xt_panic_widgets ; 

kern_return_t
xnupost_register_panic_widget(xt_panic_widget_func funcp, const char * funcname, void * context, void ** outval)
{
	if (xt_panic_widgets.xtp_context_p != NULL || xt_panic_widgets.xtp_func != NULL)
		return KERN_RESOURCE_SHORTAGE;

	xt_panic_widgets.xtp_context_p = context;
	xt_panic_widgets.xtp_func      = funcp;
	xt_panic_widgets.xtp_func_name = funcname;
	xt_panic_widgets.xtp_outval_p  = outval;

	return KERN_SUCCESS;
}