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
typedef  int /*<<< orphan*/  u8 ;
struct eap_sm {int dummy; } ;
struct eap_peer_config {size_t new_password_len; int /*<<< orphan*/  const* new_password; } ;

/* Variables and functions */
 struct eap_peer_config* eap_get_config (struct eap_sm*) ; 

const u8 * eap_get_config_new_password(struct eap_sm *sm, size_t *len)
{
	struct eap_peer_config *config = eap_get_config(sm);
	if (config == NULL)
		return NULL;
	*len = config->new_password_len;
	return config->new_password;
}