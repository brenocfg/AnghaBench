#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  errmsg; int /*<<< orphan*/  sqlstate; } ;
typedef  TYPE_1__ network_mysqld_err_packet_t ;

/* Variables and functions */
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  g_free (TYPE_1__*) ; 
 int /*<<< orphan*/  g_string_free (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void network_mysqld_err_packet_free(network_mysqld_err_packet_t *err_packet) {
	if (!err_packet) return;

	g_string_free(err_packet->sqlstate, TRUE);
	g_string_free(err_packet->errmsg, TRUE);

	g_free(err_packet);
}