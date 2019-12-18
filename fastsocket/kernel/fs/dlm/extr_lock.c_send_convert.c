#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct dlm_rsb {TYPE_1__* res_ls; } ;
struct dlm_lkb {int /*<<< orphan*/  lkb_flags; } ;
struct TYPE_4__ {int /*<<< orphan*/  m_flags; scalar_t__ m_result; int /*<<< orphan*/  m_type; } ;
struct TYPE_3__ {TYPE_2__ ls_stub_ms; } ;

/* Variables and functions */
 int /*<<< orphan*/  DLM_MSG_CONVERT ; 
 int /*<<< orphan*/  DLM_MSG_CONVERT_REPLY ; 
 int /*<<< orphan*/  __receive_convert_reply (struct dlm_rsb*,struct dlm_lkb*,TYPE_2__*) ; 
 scalar_t__ down_conversion (struct dlm_lkb*) ; 
 int /*<<< orphan*/  remove_from_waiters (struct dlm_lkb*,int /*<<< orphan*/ ) ; 
 int send_common (struct dlm_rsb*,struct dlm_lkb*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int send_convert(struct dlm_rsb *r, struct dlm_lkb *lkb)
{
	int error;

	error = send_common(r, lkb, DLM_MSG_CONVERT);

	/* down conversions go without a reply from the master */
	if (!error && down_conversion(lkb)) {
		remove_from_waiters(lkb, DLM_MSG_CONVERT_REPLY);
		r->res_ls->ls_stub_ms.m_type = DLM_MSG_CONVERT_REPLY;
		r->res_ls->ls_stub_ms.m_result = 0;
		r->res_ls->ls_stub_ms.m_flags = lkb->lkb_flags;
		__receive_convert_reply(r, lkb, &r->res_ls->ls_stub_ms);
	}

	return error;
}