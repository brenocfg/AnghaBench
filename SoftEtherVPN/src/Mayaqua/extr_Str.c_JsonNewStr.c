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
typedef  int /*<<< orphan*/  UINT ;
typedef  int /*<<< orphan*/  JSON_VALUE ;

/* Variables and functions */
 int /*<<< orphan*/  StrLen (char*) ; 
 int /*<<< orphan*/  is_valid_utf8 (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * json_value_init_string_no_copy (char*) ; 
 int /*<<< orphan*/  parson_free (char*) ; 
 char* parson_strndup (char*,int /*<<< orphan*/ ) ; 

JSON_VALUE * JsonNewStr(char *string) {
	char *copy = NULL;
	JSON_VALUE *value;
	UINT string_len = 0;
	if (string == NULL) {
		return NULL;
	}
	string_len = StrLen(string);
	if (!is_valid_utf8(string, string_len)) {
		return NULL;
	}
	copy = parson_strndup(string, string_len);
	if (copy == NULL) {
		return NULL;
	}
	value = json_value_init_string_no_copy(copy);
	if (value == NULL) {
		parson_free(copy);
	}
	return value;
}