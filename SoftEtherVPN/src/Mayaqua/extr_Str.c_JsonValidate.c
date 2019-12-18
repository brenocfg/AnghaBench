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
typedef  int UINT ;
typedef  int /*<<< orphan*/  JSON_VALUE ;
typedef  int /*<<< orphan*/  JSON_OBJECT ;
typedef  int /*<<< orphan*/  JSON_ARRAY ;

/* Variables and functions */
 int JSON_RET_ERROR ; 
 int JSON_RET_OK ; 
#define  JSON_TYPE_ARRAY 134 
#define  JSON_TYPE_BOOL 133 
#define  JSON_TYPE_ERROR 132 
#define  JSON_TYPE_NULL 131 
#define  JSON_TYPE_NUMBER 130 
#define  JSON_TYPE_OBJECT 129 
#define  JSON_TYPE_STRING 128 
 int /*<<< orphan*/ * JsonArrayGet (int /*<<< orphan*/ *,int) ; 
 int JsonArrayGetCount (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * JsonGet (int /*<<< orphan*/ *,char*) ; 
 int JsonGetCount (int /*<<< orphan*/ *) ; 
 char* JsonGetName (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/ * JsonValueGetArray (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * JsonValueGetObject (int /*<<< orphan*/ *) ; 
 int JsonValueGetType (int /*<<< orphan*/ *) ; 

UINT JsonValidate(JSON_VALUE *schema, JSON_VALUE *value) {
	JSON_VALUE *temp_schema_value = NULL, *temp_value = NULL;
	JSON_ARRAY *schema_array = NULL, *value_array = NULL;
	JSON_OBJECT *schema_object = NULL, *value_object = NULL;
	UINT schema_type = JSON_TYPE_ERROR, value_type = JSON_TYPE_ERROR;
	char *key = NULL;
	UINT i = 0, count = 0;
	if (schema == NULL || value == NULL) {
		return JSON_RET_ERROR;
	}
	schema_type = JsonValueGetType(schema);
	value_type = JsonValueGetType(value);
	if (schema_type != value_type && schema_type != JSON_TYPE_NULL) { /* null represents all values */
		return JSON_RET_ERROR;
	}
	switch (schema_type) {
	case JSON_TYPE_ARRAY:
		schema_array = JsonValueGetArray(schema);
		value_array = JsonValueGetArray(value);
		count = JsonArrayGetCount(schema_array);
		if (count == 0) {
			return JSON_RET_OK; /* Empty array allows all types */
		}
		/* Get first value from array, rest is ignored */
		temp_schema_value = JsonArrayGet(schema_array, 0);
		for (i = 0; i < JsonArrayGetCount(value_array); i++) {
			temp_value = JsonArrayGet(value_array, i);
			if (JsonValidate(temp_schema_value, temp_value) == JSON_RET_ERROR) {
				return JSON_RET_ERROR;
			}
		}
		return JSON_RET_OK;
	case JSON_TYPE_OBJECT:
		schema_object = JsonValueGetObject(schema);
		value_object = JsonValueGetObject(value);
		count = JsonGetCount(schema_object);
		if (count == 0) {
			return JSON_RET_OK; /* Empty object allows all objects */
		}
		else if (JsonGetCount(value_object) < count) {
			return JSON_RET_ERROR; /* Tested object mustn't have less name-value pairs than schema */
		}
		for (i = 0; i < count; i++) {
			key = JsonGetName(schema_object, i);
			temp_schema_value = JsonGet(schema_object, key);
			temp_value = JsonGet(value_object, key);
			if (temp_value == NULL) {
				return JSON_RET_ERROR;
			}
			if (JsonValidate(temp_schema_value, temp_value) == JSON_RET_ERROR) {
				return JSON_RET_ERROR;
			}
		}
		return JSON_RET_OK;
	case JSON_TYPE_STRING: case JSON_TYPE_NUMBER: case JSON_TYPE_BOOL: case JSON_TYPE_NULL:
		return JSON_RET_OK; /* equality already tested before switch */
	case JSON_TYPE_ERROR: default:
		return JSON_RET_ERROR;
	}
}