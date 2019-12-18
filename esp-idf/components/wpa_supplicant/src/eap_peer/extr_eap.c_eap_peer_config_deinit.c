#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int /*<<< orphan*/  new_password; int /*<<< orphan*/  password; int /*<<< orphan*/  identity; int /*<<< orphan*/  anonymous_identity; } ;
struct eap_sm {TYPE_1__ config; } ;
struct eap_peer_config {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  os_bzero (TYPE_1__*,int) ; 
 int /*<<< orphan*/  os_free (int /*<<< orphan*/ ) ; 

void eap_peer_config_deinit(struct eap_sm *sm)
{
	if (!sm)
		return;

	os_free(sm->config.anonymous_identity);
	os_free(sm->config.identity);
	os_free(sm->config.password);
	os_free(sm->config.new_password);
	os_bzero(&sm->config, sizeof(struct eap_peer_config));
}