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
struct wps_credential {int /*<<< orphan*/  key_len; int /*<<< orphan*/  key; int /*<<< orphan*/  key_idx; int /*<<< orphan*/  encr_type; int /*<<< orphan*/  auth_type; int /*<<< orphan*/  ssid_len; int /*<<< orphan*/  ssid; } ;

/* Variables and functions */
 int /*<<< orphan*/  os_memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void wps_cred_update(struct wps_credential *dst,
			    struct wps_credential *src)
{
	os_memcpy(dst->ssid, src->ssid, sizeof(dst->ssid));
	dst->ssid_len = src->ssid_len;
	dst->auth_type = src->auth_type;
	dst->encr_type = src->encr_type;
	dst->key_idx = src->key_idx;
	os_memcpy(dst->key, src->key, sizeof(dst->key));
	dst->key_len = src->key_len;
}