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

/* Variables and functions */
 int SNMP_ERR_GENERR ; 
 int SNMP_ERR_NOERROR ; 
 int /*<<< orphan*/  lsock_remove ; 
 int /*<<< orphan*/ * my_trans ; 
 int /*<<< orphan*/ * trans_first_port (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  trans_iter_port (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int trans_unregister (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
lsock_stop(int force)
{

	if (my_trans != NULL) {
		if (!force && trans_first_port(my_trans) != NULL)
			return (SNMP_ERR_GENERR);
		trans_iter_port(my_trans, lsock_remove, 0);
		return (trans_unregister(my_trans));
	}
	return (SNMP_ERR_NOERROR);
}