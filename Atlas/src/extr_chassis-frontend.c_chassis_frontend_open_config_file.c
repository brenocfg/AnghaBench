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
typedef  int /*<<< orphan*/  GKeyFile ;
typedef  int /*<<< orphan*/  GError ;

/* Variables and functions */
 scalar_t__ FALSE ; 
 int /*<<< orphan*/  G_KEY_FILE_NONE ; 
 int /*<<< orphan*/  g_key_file_free (int /*<<< orphan*/ *) ; 
 scalar_t__ g_key_file_load_from_file (int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/ * g_key_file_new () ; 
 int /*<<< orphan*/  g_key_file_set_list_separator (int /*<<< orphan*/ *,char) ; 

GKeyFile *chassis_frontend_open_config_file(const char *filename, GError **gerr) {
	GKeyFile *keyfile;
/*
	if (chassis_filemode_check_full(filename, CHASSIS_FILEMODE_SECURE_MASK, gerr) != 0) {
		return NULL;
	}
*/
	keyfile = g_key_file_new();
	g_key_file_set_list_separator(keyfile, ',');

	if (FALSE == g_key_file_load_from_file(keyfile, filename, G_KEY_FILE_NONE, gerr)) {
		g_key_file_free(keyfile);

		return NULL;
	}

	return keyfile;
}