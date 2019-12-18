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
struct dlm_rsb {int res_length; TYPE_1__* res_ls; } ;
struct dlm_mhandle {int dummy; } ;
struct dlm_message {int dummy; } ;
struct dlm_lkb {int /*<<< orphan*/  lkb_lvbptr; } ;
struct TYPE_2__ {int ls_lvblen; } ;

/* Variables and functions */
#define  DLM_MSG_CONVERT 135 
#define  DLM_MSG_CONVERT_REPLY 134 
#define  DLM_MSG_GRANT 133 
#define  DLM_MSG_LOOKUP 132 
#define  DLM_MSG_REMOVE 131 
#define  DLM_MSG_REQUEST 130 
#define  DLM_MSG_REQUEST_REPLY 129 
#define  DLM_MSG_UNLOCK 128 
 int _create_message (TYPE_1__*,int,int,int,struct dlm_message**,struct dlm_mhandle**) ; 

__attribute__((used)) static int create_message(struct dlm_rsb *r, struct dlm_lkb *lkb,
			  int to_nodeid, int mstype,
			  struct dlm_message **ms_ret,
			  struct dlm_mhandle **mh_ret)
{
	int mb_len = sizeof(struct dlm_message);

	switch (mstype) {
	case DLM_MSG_REQUEST:
	case DLM_MSG_LOOKUP:
	case DLM_MSG_REMOVE:
		mb_len += r->res_length;
		break;
	case DLM_MSG_CONVERT:
	case DLM_MSG_UNLOCK:
	case DLM_MSG_REQUEST_REPLY:
	case DLM_MSG_CONVERT_REPLY:
	case DLM_MSG_GRANT:
		if (lkb && lkb->lkb_lvbptr)
			mb_len += r->res_ls->ls_lvblen;
		break;
	}

	return _create_message(r->res_ls, mb_len, to_nodeid, mstype,
			       ms_ret, mh_ret);
}