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
struct TYPE_3__ {int opcode; } ;
struct TYPE_4__ {TYPE_1__ rsp; } ;
union viosrp_iu {TYPE_2__ srp; } ;
typedef  int u8 ;
struct iu_entry {int dummy; } ;

/* Variables and functions */
#define  SRP_AER_REQ 138 
#define  SRP_AER_RSP 137 
#define  SRP_CMD 136 
#define  SRP_CRED_REQ 135 
#define  SRP_CRED_RSP 134 
#define  SRP_I_LOGOUT 133 
#define  SRP_LOGIN_REQ 132 
#define  SRP_LOGIN_RSP 131 
#define  SRP_RSP 130 
#define  SRP_TSK_MGMT 129 
#define  SRP_T_LOGOUT 128 
 int /*<<< orphan*/  eprintk (char*,int) ; 
 int /*<<< orphan*/  process_login (struct iu_entry*) ; 
 int process_tsk_mgmt (struct iu_entry*) ; 
 int /*<<< orphan*/  queue_cmd (struct iu_entry*) ; 
 union viosrp_iu* vio_iu (struct iu_entry*) ; 

__attribute__((used)) static int process_srp_iu(struct iu_entry *iue)
{
	union viosrp_iu *iu = vio_iu(iue);
	int done = 1;
	u8 opcode = iu->srp.rsp.opcode;

	switch (opcode) {
	case SRP_LOGIN_REQ:
		process_login(iue);
		break;
	case SRP_TSK_MGMT:
		done = process_tsk_mgmt(iue);
		break;
	case SRP_CMD:
		queue_cmd(iue);
		done = 0;
		break;
	case SRP_LOGIN_RSP:
	case SRP_I_LOGOUT:
	case SRP_T_LOGOUT:
	case SRP_RSP:
	case SRP_CRED_REQ:
	case SRP_CRED_RSP:
	case SRP_AER_REQ:
	case SRP_AER_RSP:
		eprintk("Unsupported type %u\n", opcode);
		break;
	default:
		eprintk("Unknown type %u\n", opcode);
	}

	return done;
}