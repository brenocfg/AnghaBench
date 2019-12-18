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
typedef  int /*<<< orphan*/  network_socket ;
typedef  int /*<<< orphan*/  guint ;
typedef  int /*<<< orphan*/  gsize ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int network_mysqld_con_send_error_full_all (int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

int network_mysqld_con_send_error_pre41_full(network_socket *con, const char *errmsg, gsize errmsg_len, guint errorcode) {
	return network_mysqld_con_send_error_full_all(con, errmsg, errmsg_len, errorcode, NULL, FALSE);
}