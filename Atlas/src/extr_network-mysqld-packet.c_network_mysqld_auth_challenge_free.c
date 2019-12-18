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
struct TYPE_4__ {scalar_t__ challenge; struct TYPE_4__* server_version_str; } ;
typedef  TYPE_1__ network_mysqld_auth_challenge ;

/* Variables and functions */
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  g_free (TYPE_1__*) ; 
 int /*<<< orphan*/  g_string_free (scalar_t__,int /*<<< orphan*/ ) ; 

void network_mysqld_auth_challenge_free(network_mysqld_auth_challenge *shake) {
	if (!shake) return;

	if (shake->server_version_str) g_free(shake->server_version_str);
	if (shake->challenge)          g_string_free(shake->challenge, TRUE);

	g_free(shake);
}