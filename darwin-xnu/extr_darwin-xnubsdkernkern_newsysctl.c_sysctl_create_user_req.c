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
typedef  void* user_addr_t ;
struct sysctl_req {size_t oldlen; size_t newlen; int lock; int /*<<< orphan*/  newfunc; int /*<<< orphan*/  oldfunc; void* newptr; void* oldptr; struct proc* p; } ;
struct proc {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  bzero (struct sysctl_req*,int) ; 
 int /*<<< orphan*/  sysctl_new_user ; 
 int /*<<< orphan*/  sysctl_old_user ; 

void sysctl_create_user_req(struct sysctl_req *req, struct proc *p, user_addr_t oldp,
							size_t oldlen, user_addr_t newp, size_t newlen)
{
	bzero(req, sizeof(*req));
	
	req->p = p;
	
	req->oldlen = oldlen;
	req->oldptr = oldp;
	
	if (newlen) {
		req->newlen = newlen;
		req->newptr = newp;
	}
	
	req->oldfunc = sysctl_old_user;
	req->newfunc = sysctl_new_user;
	req->lock = 1;

	return;
}