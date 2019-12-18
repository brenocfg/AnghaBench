#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {TYPE_2__* client; TYPE_1__* server; TYPE_4__* charset_connection; TYPE_4__* charset_results; TYPE_4__* charset_client; } ;
typedef  TYPE_3__ network_mysqld_con ;
struct TYPE_10__ {scalar_t__ len; } ;
struct TYPE_8__ {int /*<<< orphan*/  charset_connection; int /*<<< orphan*/  charset_results; int /*<<< orphan*/  charset_client; } ;
struct TYPE_7__ {int /*<<< orphan*/  charset_connection; int /*<<< orphan*/  charset_results; int /*<<< orphan*/  charset_client; } ;
typedef  TYPE_4__ GString ;

/* Variables and functions */
 int /*<<< orphan*/  S (TYPE_4__*) ; 
 int /*<<< orphan*/  g_string_assign_len (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void update_charset(network_mysqld_con* con) {
	GString* charset_client     = con->charset_client;
	GString* charset_results    = con->charset_results;
	GString* charset_connection = con->charset_connection;

	if (charset_client->len > 0) {
		if (con->server) g_string_assign_len(con->server->charset_client, S(charset_client));
		g_string_assign_len(con->client->charset_client, S(charset_client));
	}

	if (charset_results->len > 0) {
		if (con->server) g_string_assign_len(con->server->charset_results, S(charset_results));
		g_string_assign_len(con->client->charset_results, S(charset_results));
	}

	if (charset_connection->len > 0) {
		if (con->server) g_string_assign_len(con->server->charset_connection, S(charset_connection));
		g_string_assign_len(con->client->charset_connection, S(charset_connection));
	}
}