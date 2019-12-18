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
typedef  int /*<<< orphan*/  JSON_OBJECT ;

/* Variables and functions */
 int /*<<< orphan*/  JSON_RET_ERROR ; 
 int /*<<< orphan*/  JsonDelete (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/ * JsonGetObj (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  parson_free (char*) ; 
 char* parson_strndup (char*,int /*<<< orphan*/ ) ; 
 char* strchr (char*,char) ; 

UINT JsonDotDelete(JSON_OBJECT *object, char *name) {
	char *dot_pos = strchr(name, '.');
	char *current_name = NULL;
	JSON_OBJECT *temp_obj = NULL;
	if (dot_pos == NULL) {
		return JsonDelete(object, name);
	}
	else {
		current_name = parson_strndup(name, (UINT)(dot_pos - name));
		temp_obj = JsonGetObj(object, current_name);
		parson_free(current_name);
		if (temp_obj == NULL) {
			return JSON_RET_ERROR;
		}
		return JsonDotDelete(temp_obj, dot_pos + 1);
	}
}