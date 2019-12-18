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
struct rds_transport {scalar_t__ t_owner; } ;

/* Variables and functions */
 int /*<<< orphan*/  module_put (scalar_t__) ; 

void rds_trans_put(struct rds_transport *trans)
{
	if (trans && trans->t_owner)
		module_put(trans->t_owner);
}