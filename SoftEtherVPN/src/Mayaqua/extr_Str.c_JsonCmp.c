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
typedef  int /*<<< orphan*/  UINT64 ;
typedef  int UINT ;
typedef  int /*<<< orphan*/  JSON_VALUE ;
typedef  int /*<<< orphan*/  JSON_OBJECT ;
typedef  int /*<<< orphan*/  JSON_ARRAY ;

/* Variables and functions */
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
 int /*<<< orphan*/  JsonValueGetBool (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  JsonValueGetNumber (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * JsonValueGetObject (int /*<<< orphan*/ *) ; 
 char* JsonValueGetStr (int /*<<< orphan*/ *) ; 
 int JsonValueGetType (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  strcmp (char*,char*) ; 

int JsonCmp(JSON_VALUE *a, JSON_VALUE *b) {
	JSON_OBJECT *a_object = NULL, *b_object = NULL;
	JSON_ARRAY *a_array = NULL, *b_array = NULL;
	char *a_string = NULL, *b_string = NULL;
	char *key = NULL;
	UINT a_count = 0, b_count = 0, i = 0;
	UINT a_type, b_type;
	UINT64 a_num, b_num;
	a_type = JsonValueGetType(a);
	b_type = JsonValueGetType(b);
	if (a_type != b_type) {
		return 0;
	}
	switch (a_type) {
	case JSON_TYPE_ARRAY:
		a_array = JsonValueGetArray(a);
		b_array = JsonValueGetArray(b);
		a_count = JsonArrayGetCount(a_array);
		b_count = JsonArrayGetCount(b_array);
		if (a_count != b_count) {
			return 0;
		}
		for (i = 0; i < a_count; i++) {
			if (!JsonCmp(JsonArrayGet(a_array, i),
				JsonArrayGet(b_array, i))) {
					return 0;
			}
		}
		return 1;
	case JSON_TYPE_OBJECT:
		a_object = JsonValueGetObject(a);
		b_object = JsonValueGetObject(b);
		a_count = JsonGetCount(a_object);
		b_count = JsonGetCount(b_object);
		if (a_count != b_count) {
			return 0;
		}
		for (i = 0; i < a_count; i++) {
			key = JsonGetName(a_object, i);
			if (!JsonCmp(JsonGet(a_object, key),
				JsonGet(b_object, key))) {
					return 0;
			}
		}
		return 1;
	case JSON_TYPE_STRING:
		a_string = JsonValueGetStr(a);
		b_string = JsonValueGetStr(b);
		if (a_string == NULL || b_string == NULL) {
			return 0; /* shouldn't happen */
		}
		return strcmp(a_string, b_string) == 0;
	case JSON_TYPE_BOOL:
		return JsonValueGetBool(a) == JsonValueGetBool(b);
	case JSON_TYPE_NUMBER:
		a_num = JsonValueGetNumber(a);
		b_num = JsonValueGetNumber(b);
		return a_num == b_num;
	case JSON_TYPE_ERROR:
		return 1;
	case JSON_TYPE_NULL:
		return 1;
	default:
		return 1;
	}
}