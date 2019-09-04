#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct image_params {TYPE_2__* ip_ndp; } ;
typedef  TYPE_3__* proc_t ;
typedef  int /*<<< orphan*/  caddr_t ;
struct TYPE_7__ {char* p_name; char* p_comm; } ;
struct TYPE_5__ {int cn_namelen; scalar_t__ cn_nameptr; } ;
struct TYPE_6__ {TYPE_1__ ni_cnd; } ;

/* Variables and functions */
 size_t MAXCOMLEN ; 
 int /*<<< orphan*/  bcopy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int) ; 

__attribute__((used)) static void
set_proc_name(struct image_params *imgp, proc_t p)
{
	int p_name_len = sizeof(p->p_name) - 1;

	if (imgp->ip_ndp->ni_cnd.cn_namelen > p_name_len) {
		imgp->ip_ndp->ni_cnd.cn_namelen = p_name_len;
	}

	bcopy((caddr_t)imgp->ip_ndp->ni_cnd.cn_nameptr, (caddr_t)p->p_name,
		(unsigned)imgp->ip_ndp->ni_cnd.cn_namelen);
	p->p_name[imgp->ip_ndp->ni_cnd.cn_namelen] = '\0';

	if (imgp->ip_ndp->ni_cnd.cn_namelen > MAXCOMLEN) {
		imgp->ip_ndp->ni_cnd.cn_namelen = MAXCOMLEN;
	}

	bcopy((caddr_t)imgp->ip_ndp->ni_cnd.cn_nameptr, (caddr_t)p->p_comm,
		(unsigned)imgp->ip_ndp->ni_cnd.cn_namelen);
	p->p_comm[imgp->ip_ndp->ni_cnd.cn_namelen] = '\0';
}