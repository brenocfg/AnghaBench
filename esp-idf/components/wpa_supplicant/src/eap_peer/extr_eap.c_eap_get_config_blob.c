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
struct wpa_config_blob {int /*<<< orphan*/ * name; } ;
struct eap_sm {struct wpa_config_blob const* blob; } ;

/* Variables and functions */
 int /*<<< orphan*/  BLOB_NAME_LEN ; 
 int BLOB_NUM ; 
 scalar_t__ os_strncmp (char const*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

const struct wpa_config_blob * eap_get_config_blob(struct eap_sm *sm,
						   const char *name)
{
	int i;

	if (!sm)
		return NULL;

	for (i = 0; i < BLOB_NUM; i++) {
		if (sm->blob[i].name == NULL)
			continue;
		if (os_strncmp(name, sm->blob[i].name, BLOB_NAME_LEN) == 0) {
			return &sm->blob[i];
		}
	}
	return NULL;
}