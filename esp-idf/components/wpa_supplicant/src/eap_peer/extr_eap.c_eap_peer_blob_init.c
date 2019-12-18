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
struct wpa_config_blob {int dummy; } ;
struct eap_sm {TYPE_1__* blob; } ;
struct TYPE_2__ {char* name; scalar_t__ data; scalar_t__ len; } ;

/* Variables and functions */
 scalar_t__ BLOB_NAME_LEN ; 
 int BLOB_NUM ; 
 int /*<<< orphan*/  CA_CERT_NAME ; 
 int /*<<< orphan*/  CLIENT_CERT_NAME ; 
 int /*<<< orphan*/  PRIVATE_KEY_NAME ; 
 scalar_t__ g_wpa_ca_cert ; 
 scalar_t__ g_wpa_ca_cert_len ; 
 scalar_t__ g_wpa_client_cert ; 
 scalar_t__ g_wpa_client_cert_len ; 
 scalar_t__ g_wpa_private_key ; 
 scalar_t__ g_wpa_private_key_len ; 
 int /*<<< orphan*/  os_bzero (TYPE_1__*,int) ; 
 int /*<<< orphan*/  os_free (char*) ; 
 int /*<<< orphan*/  os_strncpy (char*,int /*<<< orphan*/ ,scalar_t__) ; 
 scalar_t__ os_zalloc (scalar_t__) ; 

int eap_peer_blob_init(struct eap_sm *sm)
{
	int i, ret;

	if (!sm)
		return -1;

	if (g_wpa_client_cert && g_wpa_client_cert_len) {
		sm->blob[0].name = (char *)os_zalloc(BLOB_NAME_LEN+1);
		if (sm->blob[0].name == NULL) {
			ret = -2;
			goto _out;
		}
		os_strncpy(sm->blob[0].name, CLIENT_CERT_NAME, BLOB_NAME_LEN+1);
		sm->blob[0].len = g_wpa_client_cert_len;
		sm->blob[0].data = g_wpa_client_cert;
	}

	if (g_wpa_private_key && g_wpa_private_key_len) {
		sm->blob[1].name = (char *)os_zalloc(BLOB_NAME_LEN+1);
		if (sm->blob[1].name == NULL) {
			ret = -2;
			goto _out;
		}
		os_strncpy(sm->blob[1].name, PRIVATE_KEY_NAME, BLOB_NAME_LEN+1);
		sm->blob[1].len = g_wpa_private_key_len;
		sm->blob[1].data = g_wpa_private_key;
	}

	if (g_wpa_ca_cert && g_wpa_ca_cert_len) {
		sm->blob[2].name = (char *)os_zalloc(BLOB_NAME_LEN+1);
		if (sm->blob[2].name == NULL) {
			ret = -2;
			goto _out;
		}
		os_strncpy(sm->blob[2].name, CA_CERT_NAME, BLOB_NAME_LEN+1);
		sm->blob[2].len = g_wpa_ca_cert_len;
		sm->blob[2].data = g_wpa_ca_cert;
	}

	return 0;
_out:
	for (i = 0; i < BLOB_NUM; i++) {
		if (sm->blob[i].name) {
			os_free(sm->blob[i].name);
			sm->blob[i].name = NULL;
		}
	}
	os_bzero(&sm->blob[0], sizeof(struct wpa_config_blob)*BLOB_NUM);

	return ret;
}