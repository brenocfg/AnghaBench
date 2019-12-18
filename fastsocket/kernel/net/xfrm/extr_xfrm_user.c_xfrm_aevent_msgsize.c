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
struct xfrm_replay_state {int dummy; } ;
struct xfrm_mark {int dummy; } ;
struct xfrm_lifetime_cur {int dummy; } ;
struct xfrm_aevent_id {int dummy; } ;

/* Variables and functions */
 size_t NLMSG_ALIGN (int) ; 
 size_t nla_total_size (int) ; 

__attribute__((used)) static inline size_t xfrm_aevent_msgsize(void)
{
	return NLMSG_ALIGN(sizeof(struct xfrm_aevent_id))
	       + nla_total_size(sizeof(struct xfrm_replay_state))
	       + nla_total_size(sizeof(struct xfrm_lifetime_cur))
	       + nla_total_size(sizeof(struct xfrm_mark))
	       + nla_total_size(4) /* XFRM_AE_RTHR */
	       + nla_total_size(4); /* XFRM_AE_ETHR */
}