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
struct dlm_ctxt {int /*<<< orphan*/  dlm_domain_handlers; int /*<<< orphan*/  dlm_hb_down; int /*<<< orphan*/  dlm_hb_up; } ;

/* Variables and functions */
 int /*<<< orphan*/  o2hb_unregister_callback (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  o2net_unregister_handler_list (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void dlm_unregister_domain_handlers(struct dlm_ctxt *dlm)
{
	o2hb_unregister_callback(NULL, &dlm->dlm_hb_up);
	o2hb_unregister_callback(NULL, &dlm->dlm_hb_down);
	o2net_unregister_handler_list(&dlm->dlm_domain_handlers);
}