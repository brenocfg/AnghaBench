#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  database; int /*<<< orphan*/  response; int /*<<< orphan*/  username; int /*<<< orphan*/  charset; int /*<<< orphan*/  max_packet_size; int /*<<< orphan*/  capabilities; } ;
typedef  TYPE_1__ network_mysqld_auth_response ;

/* Variables and functions */
 int /*<<< orphan*/  S (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  g_string_assign_len (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_1__* network_mysqld_auth_response_new () ; 

network_mysqld_auth_response *network_mysqld_auth_response_copy(network_mysqld_auth_response *src) {
	network_mysqld_auth_response *dst;

	if (!src) return NULL;

	dst = network_mysqld_auth_response_new();
	dst->capabilities    = src->capabilities;
	dst->max_packet_size = src->max_packet_size;
	dst->charset         = src->charset;
	g_string_assign_len(dst->username, S(src->username));
	g_string_assign_len(dst->response, S(src->response));
	g_string_assign_len(dst->database, S(src->database));

	return dst;
}