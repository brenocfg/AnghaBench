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
typedef  scalar_t__ UINT ;
typedef  int /*<<< orphan*/  JSON_VALUE ;
typedef  int /*<<< orphan*/  JSON_OBJECT ;

/* Variables and functions */
 scalar_t__ JSON_RET_ERROR ; 
 int /*<<< orphan*/  JsonFree (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * JsonGetObj (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/ * JsonNewObject () ; 
 scalar_t__ JsonSet (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ *) ; 
 scalar_t__ json_object_add (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  parson_free (char*) ; 
 char* parson_strndup (char*,scalar_t__) ; 
 char* strchr (char*,char) ; 

UINT JsonDotSet(JSON_OBJECT *object, char *name, JSON_VALUE *value) {
	char *dot_pos = NULL;
	char *current_name = NULL;
	JSON_OBJECT *temp_obj = NULL;
	JSON_VALUE *new_value = NULL;
	if (object == NULL || name == NULL || value == NULL) {
		return JSON_RET_ERROR;
	}
	dot_pos = strchr(name, '.');
	if (dot_pos == NULL) {
		return JsonSet(object, name, value);
	}
	else {
		current_name = parson_strndup(name, (UINT)(dot_pos - name));
		temp_obj = JsonGetObj(object, current_name);
		if (temp_obj == NULL) {
			new_value = JsonNewObject();
			if (new_value == NULL) {
				parson_free(current_name);
				return JSON_RET_ERROR;
			}
			if (json_object_add(object, current_name, new_value) == JSON_RET_ERROR) {
				JsonFree(new_value);
				parson_free(current_name);
				return JSON_RET_ERROR;
			}
			temp_obj = JsonGetObj(object, current_name);
		}
		parson_free(current_name);
		return JsonDotSet(temp_obj, dot_pos + 1, value);
	}
}