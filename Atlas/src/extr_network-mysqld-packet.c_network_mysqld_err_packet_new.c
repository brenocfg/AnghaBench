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
typedef  int /*<<< orphan*/  network_mysqld_err_packet_t ;

/* Variables and functions */
 int /*<<< orphan*/  NETWORK_MYSQLD_PROTOCOL_VERSION_41 ; 
 int /*<<< orphan*/ * network_mysqld_err_packet_new_full (int /*<<< orphan*/ ) ; 

network_mysqld_err_packet_t *network_mysqld_err_packet_new() {
	return network_mysqld_err_packet_new_full(NETWORK_MYSQLD_PROTOCOL_VERSION_41);
}