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
struct rds_sock {int dummy; } ;
typedef  int /*<<< orphan*/  __be32 ;
typedef  int /*<<< orphan*/  __be16 ;

/* Variables and functions */
 int /*<<< orphan*/  SOCK_DEAD ; 
 int /*<<< orphan*/  ntohs (int /*<<< orphan*/ ) ; 
 struct rds_sock* rds_bind_lookup (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rds_rs_to_sk (struct rds_sock*) ; 
 int /*<<< orphan*/  rds_sock_addref (struct rds_sock*) ; 
 int /*<<< orphan*/  rdsdebug (char*,struct rds_sock*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sock_flag (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

struct rds_sock *rds_find_bound(__be32 addr, __be16 port)
{
	struct rds_sock *rs;

	rs = rds_bind_lookup(addr, port, NULL);

	if (rs && !sock_flag(rds_rs_to_sk(rs), SOCK_DEAD))
		rds_sock_addref(rs);
	else
		rs = NULL;

	rdsdebug("returning rs %p for %pI4:%u\n", rs, &addr,
		ntohs(port));
	return rs;
}