#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct ucred {int dummy; } ;
struct socket {TYPE_1__* ops; } ;
struct TYPE_8__ {int /*<<< orphan*/  gid; int /*<<< orphan*/  uid; int /*<<< orphan*/  pid; } ;
struct scm_cookie {TYPE_2__* fp; struct cred* cred; TYPE_3__ creds; struct pid* pid; } ;
struct pid {int dummy; } ;
struct msghdr {int dummy; } ;
struct cred {int /*<<< orphan*/  egid; int /*<<< orphan*/  gid; int /*<<< orphan*/  euid; int /*<<< orphan*/  uid; } ;
struct cmsghdr {scalar_t__ cmsg_level; int cmsg_type; int /*<<< orphan*/  cmsg_len; } ;
struct TYPE_7__ {int /*<<< orphan*/  count; } ;
struct TYPE_6__ {int /*<<< orphan*/  family; } ;

/* Variables and functions */
 int /*<<< orphan*/  CMSG_DATA (struct cmsghdr*) ; 
 struct cmsghdr* CMSG_FIRSTHDR (struct msghdr*) ; 
 int /*<<< orphan*/  CMSG_LEN (int) ; 
 struct cmsghdr* CMSG_NXTHDR (struct msghdr*,struct cmsghdr*) ; 
 int /*<<< orphan*/  CMSG_OK (struct msghdr*,struct cmsghdr*) ; 
 int EINVAL ; 
 int ENOMEM ; 
 int ESRCH ; 
 int /*<<< orphan*/  PF_UNIX ; 
#define  SCM_CREDENTIALS 129 
#define  SCM_RIGHTS 128 
 scalar_t__ SOL_SOCKET ; 
 struct pid* find_get_pid (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (TYPE_2__*) ; 
 int /*<<< orphan*/  memcpy (TYPE_3__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  pid_vnr (struct pid*) ; 
 struct cred* prepare_creds () ; 
 int /*<<< orphan*/  put_cred (struct cred*) ; 
 int /*<<< orphan*/  put_pid (struct pid*) ; 
 int scm_check_creds (TYPE_3__*) ; 
 int /*<<< orphan*/  scm_destroy (struct scm_cookie*) ; 
 int scm_fp_copy (struct cmsghdr*,TYPE_2__**) ; 

int __scm_send(struct socket *sock, struct msghdr *msg, struct scm_cookie *p)
{
	struct cmsghdr *cmsg;
	int err;

	for (cmsg = CMSG_FIRSTHDR(msg); cmsg; cmsg = CMSG_NXTHDR(msg, cmsg))
	{
		err = -EINVAL;

		/* Verify that cmsg_len is at least sizeof(struct cmsghdr) */
		/* The first check was omitted in <= 2.2.5. The reasoning was
		   that parser checks cmsg_len in any case, so that
		   additional check would be work duplication.
		   But if cmsg_level is not SOL_SOCKET, we do not check
		   for too short ancillary data object at all! Oops.
		   OK, let's add it...
		 */
		if (!CMSG_OK(msg, cmsg))
			goto error;

		if (cmsg->cmsg_level != SOL_SOCKET)
			continue;

		switch (cmsg->cmsg_type)
		{
		case SCM_RIGHTS:
			if (!sock->ops || sock->ops->family != PF_UNIX)
				goto error;
			err=scm_fp_copy(cmsg, &p->fp);
			if (err<0)
				goto error;
			break;
		case SCM_CREDENTIALS:
			if (cmsg->cmsg_len != CMSG_LEN(sizeof(struct ucred)))
				goto error;
			memcpy(&p->creds, CMSG_DATA(cmsg), sizeof(struct ucred));
			err = scm_check_creds(&p->creds);
			if (err)
				goto error;

			if (!p->pid || pid_vnr(p->pid) != p->creds.pid) {
				struct pid *pid;
				err = -ESRCH;
				pid = find_get_pid(p->creds.pid);
				if (!pid)
					goto error;
				put_pid(p->pid);
				p->pid = pid;
			}

			if (!p->cred ||
			    (p->cred->euid != p->creds.uid) ||
			    (p->cred->egid != p->creds.gid)) {
				struct cred *cred;
				err = -ENOMEM;
				cred = prepare_creds();
				if (!cred)
					goto error;

				cred->uid = cred->euid = p->creds.uid;
				cred->gid = cred->egid = p->creds.gid;
				if (p->cred)
					put_cred(p->cred);
				p->cred = cred;
			}
			break;
		default:
			goto error;
		}
	}

	if (p->fp && !p->fp->count)
	{
		kfree(p->fp);
		p->fp = NULL;
	}
	return 0;

error:
	scm_destroy(p);
	return err;
}