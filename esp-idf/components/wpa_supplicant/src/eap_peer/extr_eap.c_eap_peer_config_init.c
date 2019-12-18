#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;
struct TYPE_4__ {int fragment_size; scalar_t__ anonymous_identity_len; scalar_t__ identity_len; scalar_t__ password_len; scalar_t__ new_password_len; int /*<<< orphan*/ * new_password; int /*<<< orphan*/ * password; int /*<<< orphan*/ * identity; int /*<<< orphan*/ * anonymous_identity; int /*<<< orphan*/ * ca_path; int /*<<< orphan*/ * ca_cert; int /*<<< orphan*/ * private_key; int /*<<< orphan*/ * client_cert; int /*<<< orphan*/  const* private_key_passwd; } ;
struct eap_sm {TYPE_2__ config; TYPE_1__* blob; } ;
struct TYPE_3__ {scalar_t__ name; } ;

/* Variables and functions */
 scalar_t__ g_wpa_anonymous_identity ; 
 scalar_t__ g_wpa_anonymous_identity_len ; 
 scalar_t__ g_wpa_new_password ; 
 scalar_t__ g_wpa_new_password_len ; 
 scalar_t__ g_wpa_password ; 
 scalar_t__ g_wpa_password_len ; 
 scalar_t__ g_wpa_username ; 
 scalar_t__ g_wpa_username_len ; 
 int /*<<< orphan*/  os_memcpy (int /*<<< orphan*/ *,scalar_t__,scalar_t__) ; 
 scalar_t__ os_zalloc (scalar_t__) ; 

int eap_peer_config_init(
	struct eap_sm *sm, const u8 *private_key_passwd,
	int private_key_passwd_len)
{
	if (!sm)
		return -1;

	sm->config.anonymous_identity = NULL;
	sm->config.identity = NULL;
	sm->config.password = NULL;
	sm->config.new_password = NULL;

	sm->config.private_key_passwd = private_key_passwd;
	sm->config.client_cert = (u8 *)sm->blob[0].name;
	sm->config.private_key = (u8 *)sm->blob[1].name;
	sm->config.ca_cert = (u8 *)sm->blob[2].name;

	sm->config.ca_path = NULL;

	sm->config.fragment_size = 1400; /* fragment size */

	/* anonymous identity */
	if (g_wpa_anonymous_identity && g_wpa_anonymous_identity_len > 0) {
	    sm->config.anonymous_identity_len = g_wpa_anonymous_identity_len;
	    sm->config.anonymous_identity = (u8 *)os_zalloc(sm->config.anonymous_identity_len);
	    if (sm->config.anonymous_identity == NULL)
		    return -2;
	    os_memcpy(sm->config.anonymous_identity, g_wpa_anonymous_identity, g_wpa_anonymous_identity_len);
	}

	/* Configre identity */
	if (g_wpa_username && g_wpa_username_len > 0) {
		sm->config.identity_len = g_wpa_username_len;
		sm->config.identity = (u8 *)os_zalloc(sm->config.identity_len);
		if (sm->config.identity == NULL) {
			return -2;
		}
		os_memcpy(sm->config.identity, g_wpa_username, g_wpa_username_len);
	}

	if (g_wpa_password && g_wpa_password_len) {
		sm->config.password_len = g_wpa_password_len;
		sm->config.password = (u8 *)os_zalloc(sm->config.password_len);
		if (sm->config.password == NULL)
			return -2;
		os_memcpy(sm->config.password, g_wpa_password, sm->config.password_len);
	}

	if (g_wpa_new_password && g_wpa_new_password_len) {
		sm->config.new_password_len = g_wpa_new_password_len;
		sm->config.new_password = (u8 *)os_zalloc(sm->config.new_password_len);
		if (sm->config.new_password == NULL)
			return -2;
		os_memcpy(sm->config.new_password, g_wpa_new_password,
			  sm->config.new_password_len);
	}

	return 0;
	
}