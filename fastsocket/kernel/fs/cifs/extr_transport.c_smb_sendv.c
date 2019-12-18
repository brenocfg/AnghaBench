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
struct smb_rqst {int rq_nvec; struct kvec* rq_iov; } ;
struct kvec {int dummy; } ;
struct TCP_Server_Info {int dummy; } ;

/* Variables and functions */
 int smb_send_rqst (struct TCP_Server_Info*,struct smb_rqst*) ; 

__attribute__((used)) static int
smb_sendv(struct TCP_Server_Info *server, struct kvec *iov, int n_vec)
{
	struct smb_rqst rqst = { .rq_iov = iov,
				 .rq_nvec = n_vec };

	return smb_send_rqst(server, &rqst);
}