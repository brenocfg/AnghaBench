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
struct socket {scalar_t__ so_pcb; } ;
struct sockaddr_ctl {int sc_len; int /*<<< orphan*/  sc_unit; int /*<<< orphan*/  sc_id; int /*<<< orphan*/  ss_sysaddr; int /*<<< orphan*/  sc_family; } ;
struct sockaddr {int dummy; } ;
struct kctl {int /*<<< orphan*/  id; } ;
struct TYPE_2__ {int /*<<< orphan*/  sc_unit; } ;
struct ctl_cb {TYPE_1__ sac; struct kctl* kctl; } ;

/* Variables and functions */
 int /*<<< orphan*/  AF_SYSTEM ; 
 int /*<<< orphan*/  AF_SYS_CONTROL ; 
 int EINVAL ; 
 int ENOTCONN ; 
 int /*<<< orphan*/  bzero (struct sockaddr_ctl*,int) ; 
 struct sockaddr* dup_sockaddr (struct sockaddr*,int) ; 

__attribute__((used)) static int
ctl_peeraddr(struct socket *so, struct sockaddr **nam)
{
	struct ctl_cb 		*kcb = (struct ctl_cb *)so->so_pcb;
	struct kctl			*kctl;
	struct sockaddr_ctl	sc;

	if (kcb == NULL)	/* sanity check */
		return (ENOTCONN);

	if ((kctl = kcb->kctl) == NULL)
		return (EINVAL);

	bzero(&sc, sizeof(struct sockaddr_ctl));
	sc.sc_len = sizeof(struct sockaddr_ctl);
	sc.sc_family = AF_SYSTEM;
	sc.ss_sysaddr = AF_SYS_CONTROL;
	sc.sc_id =  kctl->id;
	sc.sc_unit = kcb->sac.sc_unit;

	*nam = dup_sockaddr((struct sockaddr *)&sc, 1);

	return (0);
}