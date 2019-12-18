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
struct rds_transport {scalar_t__ (* laddr_check ) (int /*<<< orphan*/ ) ;int /*<<< orphan*/  t_owner; } ;
typedef  int /*<<< orphan*/  __be32 ;

/* Variables and functions */
 scalar_t__ IN_LOOPBACK (int /*<<< orphan*/ ) ; 
 unsigned int RDS_TRANS_COUNT ; 
 int /*<<< orphan*/  down_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ntohl (int /*<<< orphan*/ ) ; 
 struct rds_transport rds_loop_transport ; 
 int /*<<< orphan*/  rds_trans_sem ; 
 scalar_t__ stub1 (int /*<<< orphan*/ ) ; 
 struct rds_transport** transports ; 
 scalar_t__ try_module_get (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  up_read (int /*<<< orphan*/ *) ; 

struct rds_transport *rds_trans_get_preferred(__be32 addr)
{
	struct rds_transport *ret = NULL;
	struct rds_transport *trans;
	unsigned int i;

	if (IN_LOOPBACK(ntohl(addr)))
		return &rds_loop_transport;

	down_read(&rds_trans_sem);
	for (i = 0; i < RDS_TRANS_COUNT; i++) {
		trans = transports[i];

		if (trans && (trans->laddr_check(addr) == 0) &&
		    (!trans->t_owner || try_module_get(trans->t_owner))) {
			ret = trans;
			break;
		}
	}
	up_read(&rds_trans_sem);

	return ret;
}