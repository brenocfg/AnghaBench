#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  network_socket_retval_t ;
struct TYPE_6__ {int /*<<< orphan*/  (* con_cleanup ) (int /*<<< orphan*/ *,TYPE_2__*) ;} ;
struct TYPE_7__ {TYPE_1__ plugins; } ;
typedef  TYPE_2__ network_mysqld_con ;
typedef  int /*<<< orphan*/  chassis ;
typedef  int /*<<< orphan*/  (* NETWORK_MYSQLD_PLUGIN_FUNC ) (int /*<<< orphan*/ *,TYPE_2__*) ;

/* Variables and functions */
 int /*<<< orphan*/  NETWORK_SOCKET_SUCCESS ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ *,TYPE_2__*) ; 

network_socket_retval_t plugin_call_cleanup(chassis *srv, network_mysqld_con *con) {
	NETWORK_MYSQLD_PLUGIN_FUNC(func) = NULL;
	network_socket_retval_t retval = NETWORK_SOCKET_SUCCESS;

	func = con->plugins.con_cleanup;
	
	if (!func) return retval;

//	LOCK_LUA(srv->priv->sc);	/*remove lock*/
	retval = (*func)(srv, con);
//	UNLOCK_LUA(srv->priv->sc);	/*remove lock*/

	return retval;
}