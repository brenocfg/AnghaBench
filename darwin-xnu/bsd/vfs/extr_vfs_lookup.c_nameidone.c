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
struct TYPE_2__ {int cn_flags; char* cn_pnbuf; int /*<<< orphan*/  cn_pnlen; } ;
struct nameidata {TYPE_1__ ni_cnd; } ;

/* Variables and functions */
 int /*<<< orphan*/  FREE_ZONE (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int HASBUF ; 
 int /*<<< orphan*/  M_NAMEI ; 

void
nameidone(struct nameidata *ndp)
{
	if (ndp->ni_cnd.cn_flags & HASBUF) {
		char *tmp = ndp->ni_cnd.cn_pnbuf;

		ndp->ni_cnd.cn_pnbuf = NULL;
		ndp->ni_cnd.cn_flags &= ~HASBUF;
		FREE_ZONE(tmp, ndp->ni_cnd.cn_pnlen, M_NAMEI);
	}
}