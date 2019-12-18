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
struct dlm_rsb {int dummy; } ;
struct dlm_lkb {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DLM_CB_BAST ; 
 int /*<<< orphan*/  dlm_add_ast (struct dlm_lkb*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ is_master_copy (struct dlm_lkb*) ; 
 int /*<<< orphan*/  send_bast (struct dlm_rsb*,struct dlm_lkb*,int) ; 

__attribute__((used)) static void queue_bast(struct dlm_rsb *r, struct dlm_lkb *lkb, int rqmode)
{
	if (is_master_copy(lkb)) {
		send_bast(r, lkb, rqmode);
	} else {
		dlm_add_ast(lkb, DLM_CB_BAST, rqmode, 0, 0);
	}
}