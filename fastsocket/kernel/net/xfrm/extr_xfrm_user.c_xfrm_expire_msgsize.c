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
struct xfrm_user_expire {int dummy; } ;
struct xfrm_mark {int dummy; } ;

/* Variables and functions */
 size_t NLMSG_ALIGN (int) ; 
 size_t nla_total_size (int) ; 

__attribute__((used)) static inline size_t xfrm_expire_msgsize(void)
{
	return NLMSG_ALIGN(sizeof(struct xfrm_user_expire))
	       + nla_total_size(sizeof(struct xfrm_mark));
}