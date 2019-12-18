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
typedef  int /*<<< orphan*/  ipc_port_t ;
typedef  int /*<<< orphan*/  host_t ;

/* Variables and functions */
 int /*<<< orphan*/  host_get_host_port (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

ipc_port_t
convert_host_to_port(
	host_t		host)
{
	ipc_port_t port;

	host_get_host_port(host, &port);
	return port;
}