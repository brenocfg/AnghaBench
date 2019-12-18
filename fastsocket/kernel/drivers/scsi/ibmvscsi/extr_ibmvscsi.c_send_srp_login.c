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
typedef  union srp_iu {int dummy; } srp_iu ;
struct srp_login_req {int req_it_iu_len; int req_buf_fmt; int /*<<< orphan*/  opcode; } ;
struct TYPE_4__ {struct srp_login_req login_req; } ;
struct TYPE_5__ {TYPE_1__ srp; } ;
struct srp_event_struct {TYPE_2__ iu; } ;
struct ibmvscsi_host_data {int /*<<< orphan*/  dev; TYPE_3__* host; int /*<<< orphan*/  request_limit; int /*<<< orphan*/  pool; } ;
struct TYPE_6__ {int /*<<< orphan*/  host_lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int SRP_BUF_FORMAT_DIRECT ; 
 int SRP_BUF_FORMAT_INDIRECT ; 
 int /*<<< orphan*/  SRP_LOGIN_REQ ; 
 int /*<<< orphan*/  VIOSRP_SRP_FORMAT ; 
 int /*<<< orphan*/  atomic_set (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ ,char*) ; 
 struct srp_event_struct* get_event_struct (int /*<<< orphan*/ *) ; 
 int ibmvscsi_send_srp_event (struct srp_event_struct*,struct ibmvscsi_host_data*,int) ; 
 int /*<<< orphan*/  init_event_struct (struct srp_event_struct*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  login_rsp ; 
 int login_timeout ; 
 int /*<<< orphan*/  memset (struct srp_login_req*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ ,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ ,unsigned long) ; 

__attribute__((used)) static int send_srp_login(struct ibmvscsi_host_data *hostdata)
{
	int rc;
	unsigned long flags;
	struct srp_login_req *login;
	struct srp_event_struct *evt_struct = get_event_struct(&hostdata->pool);

	BUG_ON(!evt_struct);
	init_event_struct(evt_struct, login_rsp,
			  VIOSRP_SRP_FORMAT, login_timeout);

	login = &evt_struct->iu.srp.login_req;
	memset(login, 0, sizeof(*login));
	login->opcode = SRP_LOGIN_REQ;
	login->req_it_iu_len = sizeof(union srp_iu);
	login->req_buf_fmt = SRP_BUF_FORMAT_DIRECT | SRP_BUF_FORMAT_INDIRECT;

	spin_lock_irqsave(hostdata->host->host_lock, flags);
	/* Start out with a request limit of 0, since this is negotiated in
	 * the login request we are just sending and login requests always
	 * get sent by the driver regardless of request_limit.
	 */
	atomic_set(&hostdata->request_limit, 0);

	rc = ibmvscsi_send_srp_event(evt_struct, hostdata, login_timeout * 2);
	spin_unlock_irqrestore(hostdata->host->host_lock, flags);
	dev_info(hostdata->dev, "sent SRP login\n");
	return rc;
}