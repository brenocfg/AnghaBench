#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int UINT ;
struct TYPE_3__ {char** names; char** values; int count; int capacity; } ;
typedef  char JSON_VALUE ;
typedef  TYPE_1__ JSON_OBJECT ;

/* Variables and functions */
 int JSON_RET_ERROR ; 
 int JSON_RET_OK ; 
 int /*<<< orphan*/  memcpy (char**,char**,int) ; 
 int /*<<< orphan*/  parson_free (char**) ; 
 scalar_t__ parson_malloc (int) ; 

__attribute__((used)) static UINT json_object_resize(JSON_OBJECT *object, UINT new_capacity) {
	char **temp_names = NULL;
	JSON_VALUE **temp_values = NULL;

	if ((object->names == NULL && object->values != NULL) ||
		(object->names != NULL && object->values == NULL) ||
		new_capacity == 0) {
			return JSON_RET_ERROR; /* Shouldn't happen */
	}
	temp_names = (char**)parson_malloc(new_capacity * sizeof(char*));
	if (temp_names == NULL) {
		return JSON_RET_ERROR;
	}
	temp_values = (JSON_VALUE**)parson_malloc(new_capacity * sizeof(JSON_VALUE*));
	if (temp_values == NULL) {
		parson_free(temp_names);
		return JSON_RET_ERROR;
	}
	if (object->names != NULL && object->values != NULL && object->count > 0) {
		memcpy(temp_names, object->names, object->count * sizeof(char*));
		memcpy(temp_values, object->values, object->count * sizeof(JSON_VALUE*));
	}
	parson_free(object->names);
	parson_free(object->values);
	object->names = temp_names;
	object->values = temp_values;
	object->capacity = new_capacity;
	return JSON_RET_OK;
}