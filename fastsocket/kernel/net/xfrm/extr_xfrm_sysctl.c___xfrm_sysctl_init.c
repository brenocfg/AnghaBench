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
struct TYPE_2__ {int sysctl_larval_drop; int sysctl_acq_expires; int /*<<< orphan*/  sysctl_aevent_rseqth; int /*<<< orphan*/  sysctl_aevent_etime; } ;
struct net {TYPE_1__ xfrm; } ;

/* Variables and functions */
 int /*<<< orphan*/  XFRM_AE_ETIME ; 
 int /*<<< orphan*/  XFRM_AE_SEQT_SIZE ; 

__attribute__((used)) static void __xfrm_sysctl_init(struct net *net)
{
	net->xfrm.sysctl_aevent_etime = XFRM_AE_ETIME;
	net->xfrm.sysctl_aevent_rseqth = XFRM_AE_SEQT_SIZE;
	net->xfrm.sysctl_larval_drop = 1;
	net->xfrm.sysctl_acq_expires = 30;
}