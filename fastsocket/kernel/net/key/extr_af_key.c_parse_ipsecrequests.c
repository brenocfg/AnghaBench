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
typedef  int /*<<< orphan*/  u8 ;
struct xfrm_policy {int dummy; } ;
struct sadb_x_policy {int sadb_x_policy_len; } ;
struct sadb_x_ipsecrequest {int sadb_x_ipsecrequest_len; } ;

/* Variables and functions */
 int parse_ipsecrequest (struct xfrm_policy*,struct sadb_x_ipsecrequest*) ; 

__attribute__((used)) static int
parse_ipsecrequests(struct xfrm_policy *xp, struct sadb_x_policy *pol)
{
	int err;
	int len = pol->sadb_x_policy_len*8 - sizeof(struct sadb_x_policy);
	struct sadb_x_ipsecrequest *rq = (void*)(pol+1);

	while (len >= sizeof(struct sadb_x_ipsecrequest)) {
		if ((err = parse_ipsecrequest(xp, rq)) < 0)
			return err;
		len -= rq->sadb_x_ipsecrequest_len;
		rq = (void*)((u8*)rq + rq->sadb_x_ipsecrequest_len);
	}
	return 0;
}