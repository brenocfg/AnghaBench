#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int u_int32_t ;
struct nlattr {int dummy; } ;
struct TYPE_3__ {scalar_t__ expires; } ;
struct nf_conn {TYPE_1__ timeout; } ;

/* Variables and functions */
 size_t CTA_TIMEOUT ; 
 int ETIME ; 
 int HZ ; 
 int /*<<< orphan*/  add_timer (TYPE_1__*) ; 
 int /*<<< orphan*/  del_timer (TYPE_1__*) ; 
 scalar_t__ jiffies ; 
 int /*<<< orphan*/  nla_get_be32 (struct nlattr const* const) ; 
 int ntohl (int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline int
ctnetlink_change_timeout(struct nf_conn *ct, const struct nlattr * const cda[])
{
	u_int32_t timeout = ntohl(nla_get_be32(cda[CTA_TIMEOUT]));

	if (!del_timer(&ct->timeout))
		return -ETIME;

	ct->timeout.expires = jiffies + timeout * HZ;
	add_timer(&ct->timeout);

	return 0;
}