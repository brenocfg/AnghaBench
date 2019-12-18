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
struct dlm_node_addr {size_t addr_count; struct dlm_node_addr** addr; int /*<<< orphan*/  list; } ;
struct connection {int /*<<< orphan*/  rwork; int /*<<< orphan*/  swork; int /*<<< orphan*/  flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  CF_CLOSE ; 
 int /*<<< orphan*/  CF_CONNECT_PENDING ; 
 int /*<<< orphan*/  CF_WRITE_PENDING ; 
 scalar_t__ cancel_work_sync (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  clean_one_writequeue (struct connection*) ; 
 int /*<<< orphan*/  clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  close_connection (struct connection*,int) ; 
 int /*<<< orphan*/  dlm_node_addrs_spin ; 
 struct dlm_node_addr* find_node_addr (int) ; 
 int /*<<< orphan*/  kfree (struct dlm_node_addr*) ; 
 int /*<<< orphan*/  list_del (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  log_print (char*,int) ; 
 struct connection* nodeid2con (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

int dlm_lowcomms_close(int nodeid)
{
	struct connection *con;
	struct dlm_node_addr *na;

	log_print("closing connection to node %d", nodeid);
	con = nodeid2con(nodeid, 0);
	if (con) {
		clear_bit(CF_CONNECT_PENDING, &con->flags);
		clear_bit(CF_WRITE_PENDING, &con->flags);
		set_bit(CF_CLOSE, &con->flags);
		if (cancel_work_sync(&con->swork))
			log_print("canceled swork for node %d", nodeid);
		if (cancel_work_sync(&con->rwork))
			log_print("canceled rwork for node %d", nodeid);
		clean_one_writequeue(con);
		close_connection(con, true);
	}

	spin_lock(&dlm_node_addrs_spin);
	na = find_node_addr(nodeid);
	if (na) {
		list_del(&na->list);
		while (na->addr_count--)
			kfree(na->addr[na->addr_count]);
		kfree(na);
	}
	spin_unlock(&dlm_node_addrs_spin);

	return 0;
}