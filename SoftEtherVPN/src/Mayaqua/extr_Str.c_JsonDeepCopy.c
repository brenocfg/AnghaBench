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
typedef  int /*<<< orphan*/  JSON_OBJECT ;
typedef  int /*<<< orphan*/  JSON_ARRAY ;

/* Variables and functions */
 int /*<<< orphan*/  JSON_RET_ERROR ; 
#define  JSON_TYPE_ARRAY 134 
#define  JSON_TYPE_BOOL 133 
#define  JSON_TYPE_ERROR 132 
#define  JSON_TYPE_NULL 131 
#define  JSON_TYPE_NUMBER 130 
#define  JSON_TYPE_OBJECT 129 
#define  JSON_TYPE_STRING 128 
 int /*<<< orphan*/ * JsonArrayGet (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  JsonArrayGetCount (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  JsonFree (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * JsonGet (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  JsonGetCount (int /*<<< orphan*/ *) ; 
 char* JsonGetName (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * JsonNewArray () ; 
 int /*<<< orphan*/ * JsonNewBool (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * JsonNewNull () ; 
 int /*<<< orphan*/ * JsonNewNumber (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * JsonNewObject () ; 
 int /*<<< orphan*/ * JsonValueGetArray (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  JsonValueGetBool (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  JsonValueGetNumber (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * JsonValueGetObject (int /*<<< orphan*/ *) ; 
 char* JsonValueGetStr (int /*<<< orphan*/ *) ; 
 int JsonValueGetType (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  json_array_add (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  json_object_add (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * json_value_init_string_no_copy (char*) ; 
 int /*<<< orphan*/  parson_free (char*) ; 
 char* parson_strdup (char*) ; 

JSON_VALUE * JsonDeepCopy(JSON_VALUE *value) {
	UINT i = 0;
	JSON_VALUE *return_value = NULL, *temp_value_copy = NULL, *temp_value = NULL;
	char *temp_string = NULL, *temp_key = NULL;
	char *temp_string_copy = NULL;
	JSON_ARRAY *temp_array = NULL, *temp_array_copy = NULL;
	JSON_OBJECT *temp_object = NULL, *temp_object_copy = NULL;

	switch (JsonValueGetType(value)) {
	case JSON_TYPE_ARRAY:
		temp_array = JsonValueGetArray(value);
		return_value = JsonNewArray();
		if (return_value == NULL) {
			return NULL;
		}
		temp_array_copy = JsonValueGetArray(return_value);
		for (i = 0; i < JsonArrayGetCount(temp_array); i++) {
			temp_value = JsonArrayGet(temp_array, i);
			temp_value_copy = JsonDeepCopy(temp_value);
			if (temp_value_copy == NULL) {
				JsonFree(return_value);
				return NULL;
			}
			if (json_array_add(temp_array_copy, temp_value_copy) == JSON_RET_ERROR) {
				JsonFree(return_value);
				JsonFree(temp_value_copy);
				return NULL;
			}
		}
		return return_value;
	case JSON_TYPE_OBJECT:
		temp_object = JsonValueGetObject(value);
		return_value = JsonNewObject();
		if (return_value == NULL) {
			return NULL;
		}
		temp_object_copy = JsonValueGetObject(return_value);
		for (i = 0; i < JsonGetCount(temp_object); i++) {
			temp_key = JsonGetName(temp_object, i);
			temp_value = JsonGet(temp_object, temp_key);
			temp_value_copy = JsonDeepCopy(temp_value);
			if (temp_value_copy == NULL) {
				JsonFree(return_value);
				return NULL;
			}
			if (json_object_add(temp_object_copy, temp_key, temp_value_copy) == JSON_RET_ERROR) {
				JsonFree(return_value);
				JsonFree(temp_value_copy);
				return NULL;
			}
		}
		return return_value;
	case JSON_TYPE_BOOL:
		return JsonNewBool(JsonValueGetBool(value));
	case JSON_TYPE_NUMBER:
		return JsonNewNumber(JsonValueGetNumber(value));
	case JSON_TYPE_STRING:
		temp_string = JsonValueGetStr(value);
		if (temp_string == NULL) {
			return NULL;
		}
		temp_string_copy = parson_strdup(temp_string);
		if (temp_string_copy == NULL) {
			return NULL;
		}
		return_value = json_value_init_string_no_copy(temp_string_copy);
		if (return_value == NULL) {
			parson_free(temp_string_copy);
		}
		return return_value;
	case JSON_TYPE_NULL:
		return JsonNewNull();
	case JSON_TYPE_ERROR:
		return NULL;
	default:
		return NULL;
	}
}