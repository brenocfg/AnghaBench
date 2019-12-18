#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct rpc_clnt {char* cl_principal; TYPE_2__* cl_program; } ;
struct TYPE_6__ {int len; char* data; } ;
struct gss_upcall_msg {char* databuf; int uid; TYPE_3__ msg; TYPE_1__* auth; } ;
struct gss_api_mech {char* gm_name; char* gm_upcall_enctypes; } ;
struct TYPE_5__ {int /*<<< orphan*/  name; } ;
struct TYPE_4__ {struct gss_api_mech* mech; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int UPCALL_BUF_LEN ; 
 void* sprintf (char*,char*,...) ; 
 int /*<<< orphan*/  strcmp (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static void gss_encode_v1_msg(struct gss_upcall_msg *gss_msg,
				struct rpc_clnt *clnt, int machine_cred)
{
	struct gss_api_mech *mech = gss_msg->auth->mech;
	char *p = gss_msg->databuf;
	int len = 0;

	gss_msg->msg.len = sprintf(gss_msg->databuf, "mech=%s uid=%d ",
				   mech->gm_name,
				   gss_msg->uid);
	p += gss_msg->msg.len;
	if (clnt->cl_principal) {
		len = sprintf(p, "target=%s ", clnt->cl_principal);
		p += len;
		gss_msg->msg.len += len;
	}
	if (machine_cred) {
		len = sprintf(p, "service=* ");
		p += len;
		gss_msg->msg.len += len;
	} else if (!strcmp(clnt->cl_program->name, "nfs4_cb")) {
		len = sprintf(p, "service=nfs ");
		p += len;
		gss_msg->msg.len += len;
	}
	if (mech->gm_upcall_enctypes) {
		len = sprintf(p, mech->gm_upcall_enctypes);
		p += len;
		gss_msg->msg.len += len;
	}
	len = sprintf(p, "\n");
	gss_msg->msg.len += len;

	gss_msg->msg.data = gss_msg->databuf;
	BUG_ON(gss_msg->msg.len > UPCALL_BUF_LEN);
}